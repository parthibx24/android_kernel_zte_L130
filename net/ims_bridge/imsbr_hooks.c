/*
 * Copyright (C) 2016 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#define pr_fmt(fmt) "imsbr: " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/netfilter_ipv6.h>
#include <linux/skbuff.h>
#include <linux/icmpv6.h>
#include <net/ip.h>
#include <net/icmp.h>
#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_core.h>
#include <uapi/linux/ims_bridge/ims_bridge.h>

#include "imsbr_core.h"
#include "imsbr_packet.h"
#include "imsbr_hooks.h"

static bool is_icmp_error(struct nf_conntrack_tuple *nft)
{
	u8 protonum = nft->dst.protonum;
	__u8 type = nft->dst.u.icmp.type;

	if (protonum == IPPROTO_ICMP) {
		if (type == ICMP_DEST_UNREACH  ||
		    type == ICMP_SOURCE_QUENCH ||
		    type == ICMP_TIME_EXCEEDED ||
		    type == ICMP_PARAMETERPROB ||
		    type == ICMP_REDIRECT)
			return true;
	} else if (protonum == IPPROTO_ICMPV6) {
		if (type < 128)
			return true;
	}

	return false;
}

int imsbr_parse_nfttuple(struct net *net, struct sk_buff *skb,
			 struct nf_conntrack_tuple *nft)
{
	struct nf_conntrack_tuple innertuple, origtuple;
	const struct nf_conntrack_l4proto *innerproto;
	const struct nf_conntrack_l3proto *l3proto;
	struct iphdr *ip = ip_hdr(skb);
	unsigned int inner_nhoff;
	u16 l3num;

	if (ip->version == 4) {
		l3num = AF_INET;
		inner_nhoff = skb_network_offset(skb) + ip_hdrlen(skb) +
			      sizeof(struct icmphdr);
	} else if (ip->version == 6) {
		l3num = AF_INET6;
		inner_nhoff = skb_network_offset(skb) + sizeof(struct ipv6hdr) +
			      sizeof(struct icmp6hdr);
	} else {
		pr_err("parse tuple fail, ver=%d\n", ip->version);
		goto fail;
	}

	if (!nf_ct_get_tuplepr(skb, skb_network_offset(skb), l3num, net,
			       nft)) {
		pr_err("parse tuple fail, len=%d, nhoff=%d, l3num=%d\n",
		       skb->len, skb_network_offset(skb), l3num);
		goto fail;
	}

	if (is_icmp_error(nft)) {
		/* If parse the inner tuple fail, we will just use the outer
		 * tuple!
		 */
		if (!nf_ct_get_tuplepr(skb, inner_nhoff, l3num, net,
				       &origtuple))
			return 0;

		rcu_read_lock();
		l3proto = __nf_ct_l3proto_find(l3num);
		innerproto = __nf_ct_l4proto_find(l3num,
						  origtuple.dst.protonum);
		/**
		 * Ordinarily, we'd expect the inverted tupleproto, but it's
		 * been preserved inside the ICMP.
		 */
		if (!nf_ct_invert_tuple(&innertuple, &origtuple,
					l3proto, innerproto)) {
			rcu_read_unlock();
			return 0;
		}

		rcu_read_unlock();
		*nft = innertuple;
	}

	return 0;

fail:
	IMSBR_STAT_INC(nfct_get_fail);
	return -1;
}

static int imsbr_get_tuple(struct net *net, struct sk_buff *skb,
			   struct nf_conntrack_tuple *nft)
{
	enum ip_conntrack_info ctinfo;
	const struct nf_conn *ct;
	int dir;

	ct = nf_ct_get(skb, &ctinfo);
	if (likely(ct)) {
		if (nf_ct_is_untracked(ct)) {
			pr_info("get untracked conntrack\n");
			IMSBR_STAT_INC(nfct_untracked);
			return -1;
		}

		dir = CTINFO2DIR(ctinfo);
		*nft = ct->tuplehash[dir].tuple;
		return 0;
	}

	IMSBR_STAT_INC(nfct_slow_path);
	return imsbr_parse_nfttuple(net, skb, nft);
}

static unsigned int nf_imsbr_input(void *priv,
				   struct sk_buff *skb,
				   const struct nf_hook_state *state)
{
	struct nf_conntrack_tuple nft;
	struct imsbr_flow *flow;

	if (!atomic_read(&imsbr_enabled))
		return NF_ACCEPT;

	if (imsbr_get_tuple(state->net, skb, &nft))
		return NF_ACCEPT;

	imsbr_nfct_debug("input", skb, &nft);

	/* rcu_read_lock hold by netfilter hook outside */
	flow = imsbr_flow_match(&nft);
	if (!flow)
		return NF_ACCEPT;

	/* Considering handover, link_type maybe LINK_AP or LINK_CP, meanwhile
	 * socket_type maybe SOCKET_AP or SOCKET_CP.
	 *
	 * But in INPUT hook, we can ignore the link_type and do the decision
	 * based on socket_type.
	 */
	if (flow->socket_type == IMSBR_SOCKET_CP) {
		pr_debug("input skb=%p relay to cp\n", skb);
		imsbr_packet_relay2cp(skb);
		return NF_STOLEN;
	}

	return NF_ACCEPT;
}

static unsigned int nf_imsbr_output(void *priv,
				    struct sk_buff *skb,
				    const struct nf_hook_state *state)
{
	struct nf_conntrack_tuple nft;
	struct imsbr_flow *flow;
	int sim, link_type;

	if (!atomic_read(&imsbr_enabled))
		return NF_ACCEPT;

	if (imsbr_get_tuple(state->net, skb, &nft))
		return NF_ACCEPT;

	imsbr_nfct_debug("output", skb, &nft);

	/* rcu_read_lock hold by netfilter hook outside */
	flow = imsbr_flow_match(&nft);
	if (!flow)
		return NF_ACCEPT;

	/* This means the packet was relayed from CP, so there's no need to
	 * have a further check!
	 */
	if (flow->socket_type == IMSBR_SOCKET_CP)
		return NF_ACCEPT;

	link_type = flow->link_type;
	sim = flow->sim_card;

	/* We assume that WIFI is at AP and LTE is at CP, but this may be
	 * broken in the future...
	 */
	if ((link_type == IMSBR_LINK_CP && !imsbr_in_lte2wifi(sim)) ||
	    (link_type == IMSBR_LINK_AP && imsbr_in_wifi2lte(sim))) {
		pr_debug("output skb=%p relay to cp\n", skb);
		/* Complete checksum manually if hw checksum offload is on */
		if (skb->ip_summed == CHECKSUM_PARTIAL)
			skb_checksum_help(skb);
		imsbr_packet_relay2cp(skb);
		return NF_STOLEN;
	}

	return NF_ACCEPT;
}

static struct nf_hook_ops nf_imsbr_ops[] __read_mostly = {
	{
		.hook		= nf_imsbr_input,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_LOCAL_IN,
		.priority	= NF_IP_PRI_FILTER - 1,
	},
	{
		.hook		= nf_imsbr_output,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_LOCAL_OUT,
		.priority	= NF_IP_PRI_FILTER - 1,
	},
	{
		.hook		= nf_imsbr_input,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_LOCAL_IN,
		.priority	= NF_IP6_PRI_FILTER - 1,
	},
	{
		.hook		= nf_imsbr_output,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_LOCAL_OUT,
		.priority	= NF_IP6_PRI_FILTER - 1,
	},
};

int __init imsbr_hooks_init(void)
{
	int err;

	err = nf_register_hooks(nf_imsbr_ops, ARRAY_SIZE(nf_imsbr_ops));
	if (err < 0) {
		pr_err("nf_register_hooks error: %d\n", err);
		return -1;
	}

	return 0;
}

void imsbr_hooks_exit(void)
{
	nf_unregister_hooks(nf_imsbr_ops, ARRAY_SIZE(nf_imsbr_ops));
}
