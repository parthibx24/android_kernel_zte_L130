/*
 * ASoC SPRD sound card support
 *
 * Copyright (C) 2015 Renesas Solutions Corp.
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include "sprd-asoc-debug.h"
#define pr_fmt(fmt) pr_sprd_fmt("BOARD")""fmt

#include <linux/clk.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/string.h>
#include <sound/jack.h>
#include <sound/simple_card.h>
#include <sound/soc-dai.h>
#include <sound/soc.h>

#ifdef CONFIG_SND_SOC_SPRD_VBC_R3P0
#include "agdsp_access.h"
#endif
#include "sprd-asoc-card-utils.h"
#include "sprd-asoc-common.h"
#include "sprd-headset.h"

#define sprd_priv_to_dev(priv) ((priv)->snd_card.dev)
#define sprd_priv_to_link(priv, i) ((priv)->snd_card.dai_link + i)
#define sprd_priv_to_props(priv, i) ((priv)->dai_props + i)

/*
 * asoc_sprd_card_ops stores an array of struct snd_soc_ops
 * and the dimention of the array through asoc_sprd_card_set_ops()
 * by specific machine driver.
 * It will be used for the parsing of dai link ops specified in dts.
 */
static struct asoc_sprd_ptr_num asoc_sprd_card_ops;

/*
 * asoc_sprd_card_compr_ops stores an array of struct snd_soc_compr_ops
 * and the dimention of the array through asoc_sprd_card_set_compr_ops()
 * by specific machine driver.
 * It will be used for the parsing of dai link compr-ops specified in dts.
 */
static struct asoc_sprd_ptr_num asoc_sprd_card_compr_ops;

/*
 * asoc_sprd_card_init stores an array of
 * int (*init)(struct snd_soc_pcm_runtime *rtd) and the dimention of the
 * array through asoc_sprd_card_set_init() by specific machine driver.
 * It will be used for the parsing of dai link init function specified
 * in dts.
 */
static struct asoc_sprd_ptr_num asoc_sprd_card_init;

/*
 * asoc_sprd_card_bhpf stores an array of
 * int (*be_hw_params_fixup)(struct snd_soc_pcm_runtime *
 * rtd, struct snd_pcm_hw_params *params)
 * and the dimention of the array through asoc_sprd_card_set_bhpf()
 * by specific machine driver.
 * It will be used for the parsing of dai link be-hw-params-fixup
 * specified in dts.
 */
static struct asoc_sprd_ptr_num asoc_sprd_card_bhpf;

void asoc_sprd_card_set_ops(struct asoc_sprd_ptr_num *pn)
{
	asoc_sprd_card_ops.p.ops = pn->p.ops;
	asoc_sprd_card_ops.num = pn->num;
}

void asoc_sprd_card_set_compr_ops(struct asoc_sprd_ptr_num *pn)
{
	asoc_sprd_card_compr_ops.p.compr_ops = pn->p.compr_ops;
	asoc_sprd_card_compr_ops.num = pn->num;
}

void asoc_sprd_card_set_init(struct asoc_sprd_ptr_num *pn)
{
	asoc_sprd_card_init.p.init = pn->p.init;
	asoc_sprd_card_init.num = pn->num;
}

void asoc_sprd_card_set_bhpf(struct asoc_sprd_ptr_num *pn)
{
	asoc_sprd_card_bhpf.p.be_hw_params_fixup = pn->p.be_hw_params_fixup;
	asoc_sprd_card_bhpf.num = pn->num;
}

int asoc_sprd_register_card(struct device *dev, struct snd_soc_card *card)
{
	int ret = 0;

#ifdef CONFIG_SND_SOC_SPRD_VBC_R3P0
	if (!agdsp_access_enable()) {
		ret = devm_snd_soc_register_card(dev, card);
		agdsp_access_disable();
	} else
		return -EINVAL;
#else
	ret = devm_snd_soc_register_card(dev, card);
#endif

	return ret;
}

static int asoc_sprd_card_parse_sprd_headset(struct device_node *node)
{
	int ret = 0;
	struct device_node *np;

	/*
	 * Parse dt configurations for sprd headset.
	 * Even without headset driver, codec could work well. So ignore the
	 * failure cases.
	 */
	np = of_parse_phandle(node, "sprd-audio-card,headset", 0);
	if (np) {
		struct platform_device *h_pdev;

		h_pdev = of_find_device_by_node(np);
		ret = sprd_headset_probe(h_pdev);
		if (ret < 0) {
			if (ret == -EPROBE_DEFER)
				return -EPROBE_DEFER;
			pr_err("ERR: [%s] probe for headset failed!\n",
			       __func__);
			/* return -ENODEV; */
		}
	} else {
		pr_err("ERR: %s parse prop 'sprd-audio-card,headset' failed!\n",
		       __func__);
		/* return -ENODEV; */
	}

	return 0;
}

static int
asoc_sprd_card_sub_parse_of(struct device_node *np,
			    struct asoc_simple_dai *dai,
			    struct device_node **p_node,
			    const char **name, int *args_count)
{
	struct of_phandle_args args;
	struct clk *clk;
	u32 val;
	int ret;

	/*
	 * Get node via "sound-dai = <&phandle port>"
	 * it will be used as xxx_of_node on soc_bind_dai_link()
	 */
	ret = of_parse_phandle_with_args(np, "sound-dai",
					 "#sound-dai-cells", 0, &args);
	if (ret) {
		pr_err("ERR: %s parse phandle '%s' failed!(%d)\n",
		       __func__, np->name, ret);
		return ret;
	}

	*p_node = args.np;

	if (args_count)
		*args_count = args.args_count;
	/* Get dai->name */
	ret = snd_soc_of_get_dai_name(np, name);
	if (ret < 0) {
		pr_err("ERR: %s get dai name for '%s' failed!(%d)\n",
		       __func__, np->name, ret);
		return ret;
	}

	/* Parse TDM slot */
	ret = snd_soc_of_parse_tdm_slot(np, &dai->tx_slot_mask,
					&dai->rx_slot_mask,
					&dai->slots, &dai->slot_width);
	if (ret) {
		pr_err("ERR: %s parse tdm for '%s' failed!(%d)\n",
		       __func__, np->name, ret);
		return ret;
	}

	/*
	 * Parse dai->sysclk come from "clocks = <&xxx>"
	 * (if system has common clock)
	 *  or "system-clock-frequency = <xxx>"
	 *  or device's module clock.
	 */
	if (of_property_read_bool(np, "clocks")) {
		clk = of_clk_get(np, 0);
		if (IS_ERR(clk)) {
			ret = PTR_ERR(clk);
			return ret;
		}

		dai->sysclk = clk_get_rate(clk);
		dai->clk = clk;
	} else if (!of_property_read_u32(np, "system-clock-frequency", &val)) {
		dai->sysclk = val;
	} else {
		clk = of_clk_get(args.np, 0);
		if (!IS_ERR(clk))
			dai->sysclk = clk_get_rate(clk);
	}

	return 0;
}

static int asoc_sprd_card_parse_daifmt(struct device_node *node,
				       struct sprd_card_data *priv,
				       struct device_node *codec,
				       char *prefix, int idx)
{
	struct snd_soc_dai_link *dai_link = sprd_priv_to_link(priv, idx);
	struct device *dev = sprd_priv_to_dev(priv);
	struct device_node *bitclkmaster = NULL;
	struct device_node *framemaster = NULL;
	unsigned int daifmt;

	daifmt = snd_soc_of_parse_daifmt(node, prefix,
					 &bitclkmaster, &framemaster);
	daifmt &= ~SND_SOC_DAIFMT_MASTER_MASK;

	if (strlen(prefix) && !bitclkmaster && !framemaster) {
		/*
		 * No dai-link level and master setting was not found from
		 * sound node level, revert back to legacy DT parsing and
		 * take the settings from codec node.
		 */
		dev_dbg(dev, "Revert to legacy daifmt parsing\n");

		daifmt = snd_soc_of_parse_daifmt(codec, NULL, NULL, NULL) |
		    (daifmt & ~SND_SOC_DAIFMT_CLOCK_MASK);
	} else {
		if (codec == bitclkmaster)
			daifmt |= (codec == framemaster) ?
			    SND_SOC_DAIFMT_CBM_CFM : SND_SOC_DAIFMT_CBM_CFS;
		else
			daifmt |= (codec == framemaster) ?
			    SND_SOC_DAIFMT_CBS_CFM : SND_SOC_DAIFMT_CBS_CFS;
	}

	dai_link->dai_fmt = daifmt;

	of_node_put(bitclkmaster);
	of_node_put(framemaster);

	return 0;
}

static int asoc_sprd_card_dai_link_of_misc(struct device_node *node,
					   struct snd_soc_dai_link *dai_link)
{
	int ret;
	u32 val[2];

	ret = of_property_read_u32(node, "ignore-pmdown-time", val);
	if (ret) {
		if (ret != -EINVAL)
			pr_warn("%s Read prop 'ignore-pmdown-time' failed.\n",
				__func__);
		dai_link->ignore_pmdown_time = 0;
	} else
		dai_link->ignore_pmdown_time = !!val[0];
	pr_debug("%s ignore_pmdown_time: %u\n", __func__,
		 dai_link->ignore_pmdown_time);

	ret = of_property_read_u32(node, "ignore-suspend", val);
	if (ret) {
		if (ret != -EINVAL)
			pr_warn("%s Read prop 'ignore-suspend' failed.\n",
				__func__);
		dai_link->ignore_suspend = 1;
	} else
		dai_link->ignore_suspend = !!val[0];
	pr_debug("%s ignore_suspend: %u\n", __func__, dai_link->ignore_suspend);

	ret = of_property_read_u32(node, "dynamic", val);
	if (ret) {
		if (ret != -EINVAL)
			pr_warn("%s Read prop 'dynamic' failed.\n", __func__);
		dai_link->dynamic = 0;
	} else
		dai_link->dynamic = !!val[0];
	pr_debug("%s dynamic: %u\n", __func__, dai_link->dynamic);

	ret = of_property_read_u32(node, "be-id", val);
	if (ret) {
		if (ret != -EINVAL)
			pr_warn("%s Read prop 'be-id' failed.\n", __func__);
		dai_link->be_id = 0;
	} else
		/* TODO: check the validity of val. */
		dai_link->be_id = val[0];
	pr_debug("%s be_id: %u\n", __func__, dai_link->be_id);

	ret = of_property_read_u32(node, "no-pcm", val);
	if (ret) {
		if (ret != -EINVAL)
			pr_warn("%s Read prop 'no-pcm' failed.\n", __func__);
		dai_link->no_pcm = 0;
	} else
		dai_link->no_pcm = !!val[0];
	pr_debug("%s no_pcm: %u\n", __func__, dai_link->no_pcm);

	ret = of_property_read_u32_array(node, "trigger", val, 2);
	if (ret) {
		if (ret != -EINVAL)
			pr_warn("%s Read prop 'trigger' failed.\n", __func__);
		dai_link->trigger[0] = 0;
		dai_link->trigger[1] = 0;
	} else {
		if (val[0] >= SND_SOC_DPCM_TRIGGER_PRE &&
		    val[0] <= SND_SOC_DPCM_TRIGGER_BESPOKE)
			dai_link->trigger[0] = val[0];
		if (val[1] >= SND_SOC_DPCM_TRIGGER_PRE &&
		    val[1] <= SND_SOC_DPCM_TRIGGER_BESPOKE)
			dai_link->trigger[1] = val[1];
	}
	pr_debug("%s trigger: %u %u\n", __func__, dai_link->trigger[0],
		 dai_link->trigger[1]);

	ret = of_property_read_u32(node, "ops", val);
	if (ret) {
		if (ret != -EINVAL)
			pr_warn("%s Read prop 'ops' failed.\n", __func__);
		dai_link->ops = NULL;
	} else {
		pr_debug("%s ops seletct: %u\n", __func__, val[0]);
		if (val[0] < asoc_sprd_card_ops.num && asoc_sprd_card_ops.p.ptr)
			dai_link->ops = &asoc_sprd_card_ops.p.ops[val[0]];
		else
			dai_link->ops = NULL;
	}

	ret = of_property_read_u32(node, "compr-ops", val);
	if (ret) {
		if (ret != -EINVAL)
			pr_warn("%s Read prop 'compr-ops' failed.\n", __func__);
		dai_link->compr_ops = NULL;
	} else {
		pr_debug("%s compr_ops seletct: %u\n", __func__, val[0]);
		if (val[0] < asoc_sprd_card_compr_ops.num
		    && asoc_sprd_card_compr_ops.p.ptr)
			dai_link->compr_ops =
			    &asoc_sprd_card_compr_ops.p.compr_ops[val[0]];
		else
			dai_link->compr_ops = NULL;
	}

	ret = of_property_read_u32(node, "init", val);
	if (ret) {
		if (ret != -EINVAL)
			pr_warn("%s Read prop 'init' failed.\n", __func__);
		dai_link->init = NULL;
	} else {
		pr_debug("%s init seletct: %u\n", __func__, val[0]);
		if (val[0] < asoc_sprd_card_init.num
		    && asoc_sprd_card_init.p.ptr)
			dai_link->init = asoc_sprd_card_init.p.init[val[0]];
		else
			dai_link->init = NULL;
	}

	ret = of_property_read_u32(node, "be-hw-params-fixup", val);
	if (ret) {
		if (ret != -EINVAL)
			pr_warn("%s Read prop 'be-hw-params-fixup' failed.\n",
				__func__);
		dai_link->be_hw_params_fixup = NULL;
	} else {
		pr_debug("%s be-hw-params-fixup seletct: %u\n",
			 __func__, val[0]);
		if (val[0] < asoc_sprd_card_bhpf.num
		    && asoc_sprd_card_bhpf.p.ptr)
			dai_link->be_hw_params_fixup =
			    asoc_sprd_card_bhpf.p.be_hw_params_fixup[val[0]];
		else
			dai_link->be_hw_params_fixup = NULL;
	}

	/* todo: add the parsing of other elements of snd_soc_dai_link. */

	return 0;
}

/*
 * If codec parsing failed, uses a dummy component(defined in
 * soc-utils.c and dummy-codec.c). If you wanna use a dummy
 * codec explicitly, you can write your dts like this,
 *	codec {
 *		sound-dai = <0 1>;
 *	};
 * first cell is '0', which indicates a dummy dai.
 * second cell:
 *	0: dummy dai with playback & capture stream;
 *	1: dummy dai with only playback.
 */
static int asoc_sprd_card_dummy_codec_sel(struct device_node *np,
					  struct snd_soc_dai_link *dai_link)
{
	int ret = 0;
	u32 val[2];

	ret = of_property_read_u32_array(np, "sound-dai", val, 2);
	if (ret) {
		pr_err("%s: read 'sound-dai' as u32 failed!(%d)\n",
		       __func__, ret);
		return ret;
	}

	if (val[0] != 0) {
		pr_err("%s: not a need of dummy dai!\n", __func__);
		return -EINVAL;
	}

	if (val[1] == 1) {	/* dummy playback-only codec */
		dai_link->codec_dai_name = "sprd-dummy-playback-dai";
		dai_link->codec_name = "sprd-dummy-playback";
	} else {
		dai_link->codec_dai_name = "snd-soc-dummy-dai";
		dai_link->codec_name = "snd-soc-dummy";
	}

	return 0;
}

static int asoc_sprd_card_dai_link_of(struct device_node *node,
				      struct sprd_card_data *priv,
				      int idx, bool is_top_level_node)
{
	struct device *dev = sprd_priv_to_dev(priv);
	struct snd_soc_dai_link *dai_link = sprd_priv_to_link(priv, idx);
	struct sprd_dai_props *dai_props = sprd_priv_to_props(priv, idx);
	struct device_node *cpu = NULL;
	struct device_node *plat = NULL;
	struct device_node *codec = NULL;
	char *name;
	char prop[128];
	char *prefix = "";
	int ret, cpu_args;
	u32 val;

	/* For single DAI link & old style of DT node */
	if (is_top_level_node)
		prefix = "sprd-audio-card,";

	snprintf(prop, sizeof(prop), "%scpu", prefix);
	cpu = of_get_child_by_name(node, prop);

	snprintf(prop, sizeof(prop), "%splat", prefix);
	plat = of_get_child_by_name(node, prop);

	snprintf(prop, sizeof(prop), "%scodec", prefix);
	codec = of_get_child_by_name(node, prop);

	if (!cpu || !codec) {
		ret = -EINVAL;
		dev_err(dev, "%s: Can't find cpu(%p) or codec(%p) DT node\n",
			__func__, cpu, codec);
		goto dai_link_of_err;
	}

	ret = asoc_sprd_card_parse_daifmt(node, priv, codec, prefix, idx);
	if (ret < 0)
		goto dai_link_of_err;

	if (!of_property_read_u32(node, "mclk-fs", &val))
		dai_props->mclk_fs = val;

	ret = asoc_sprd_card_sub_parse_of(cpu, &dai_props->cpu_dai,
					  &dai_link->cpu_of_node,
					  &dai_link->cpu_dai_name, &cpu_args);
	if (ret < 0)
		goto dai_link_of_err;

	ret = asoc_sprd_card_sub_parse_of(codec, &dai_props->codec_dai,
					  &dai_link->codec_of_node,
					  &dai_link->codec_dai_name, NULL);
	if (ret < 0) {
		if (-ENOENT == ret) {
			pr_info("%s: parse for codec failed. Go to use a dummy codec.\n",
			     __func__);
			ret = asoc_sprd_card_dummy_codec_sel(codec, dai_link);
			if (ret)
				goto dai_link_of_err;
		}
	}

	if (!dai_link->cpu_dai_name || !dai_link->codec_dai_name) {
		dev_err(dev, "%s: xx_dai_name is NULL\n", __func__);
		goto dai_link_of_err;
	}

	if (plat) {
		struct of_phandle_args args;

		ret = of_parse_phandle_with_args(plat, "sound-dai",
						 "#sound-dai-cells", 0, &args);
		dai_link->platform_of_node = args.np;
	} else {
		/* Assumes platform == cpu */
		dai_link->platform_of_node = dai_link->cpu_of_node;
	}

	/* DAI link name is created from CPU/CODEC dai name */
	name = devm_kzalloc(dev,
			    strlen(dai_link->cpu_dai_name) +
			    strlen(dai_link->codec_dai_name) + 2, GFP_KERNEL);
	if (!name) {
		ret = -ENOMEM;
		goto dai_link_of_err;
	}

	sprintf(name, "%s-%s", dai_link->cpu_dai_name,
		dai_link->codec_dai_name);
	dai_link->name = dai_link->stream_name = name;

	ret = asoc_sprd_card_dai_link_of_misc(node, dai_link);
	if (ret)
		goto dai_link_of_err;

	dev_dbg(dev, "\tname : %s\n", dai_link->stream_name);
	dev_dbg(dev, "\tformat : %04x\n", dai_link->dai_fmt);
	dev_dbg(dev, "\tcpu : %s / %d\n",
		dai_link->cpu_dai_name, dai_props->cpu_dai.sysclk);
	dev_dbg(dev, "\tcodec : %s / %d\n",
		dai_link->codec_dai_name, dai_props->codec_dai.sysclk);

	/*
	 * In soc_bind_dai_link() will check cpu name after
	 * of_node matching if dai_link has cpu_dai_name.
	 * but, it will never match if name was created by
	 * fmt_single_name() remove cpu_dai_name if cpu_args
	 * was 0. See:
	 *      fmt_single_name()
	 *      fmt_multiple_name()
	 */
	if (!cpu_args)
		dai_link->cpu_dai_name = NULL;

dai_link_of_err:
	of_node_put(cpu);
	if (plat)
		of_node_put(plat);
	of_node_put(codec);

	return ret;
}

static int asoc_sprd_card_parse_of(struct device_node *node,
				   struct sprd_card_data *priv)
{
	struct device *dev = sprd_priv_to_dev(priv);
	enum of_gpio_flags flags;
	u32 val;
	int ret;

	if (!node) {
		dev_err(dev, "%s: node is NULL\n", __func__);
		return -EINVAL;
	}

	/* Parse the card name from DT */
	snd_soc_of_parse_card_name(&priv->snd_card, "sprd-audio-card,name");

	/* The off-codec widgets */
	if (of_property_read_bool(node, "sprd-audio-card,widgets")) {
		ret = snd_soc_of_parse_audio_simple_widgets(&priv->snd_card,
							    "sprd-audio-card,widgets");
		if (ret)
			return ret;
	}

	/* DAPM routes */
	if (of_property_read_bool(node, "sprd-audio-card,routing")) {
		ret = snd_soc_of_parse_audio_routing(&priv->snd_card,
						     "sprd-audio-card,routing");
		if (ret)
			return ret;
	}

	/* Factor to mclk, used in hw_params() */
	ret = of_property_read_u32(node, "sprd-audio-card,mclk-fs", &val);
	if (ret == 0)
		priv->mclk_fs = val;

	dev_dbg(dev, "New sprd-card: %s\n", priv->snd_card.name ?
		priv->snd_card.name : "");
	ret = of_property_read_u32(node, "sprd-audio-card,fm-hw-rate", &val);
	if (ret == 0)
		priv->fm_hw_rate = val;
	dev_dbg(dev, "fm-hw-rate = %u\n", priv->fm_hw_rate);

	ret =
	    of_property_read_u32(node, "sprd-audio-card,codec-replace-adc-rate",
				 &val);
	if (ret == 0)
		priv->codec_replace_adc_rate = val;
	dev_dbg(dev, "codec_replace_adc_rate=%u\n",
		priv->codec_replace_adc_rate);

	ret = of_property_read_u32(node, "sprd-audio-card,fm-open-src", &val);
	if (ret == 0)
		priv->is_fm_open_src = val;
	dev_dbg(dev, "is_fm_open_src=%u\n", priv->is_fm_open_src);

	/* Single/Muti DAI link(s) & New style of DT node */
	if (of_get_child_by_name(node, "sprd-audio-card,dai-link")) {
		struct device_node *np = NULL;
		int i = 0;

		for_each_child_of_node(node, np) {
			dev_dbg(dev, "\tlink %d:\n", i);
			ret = asoc_sprd_card_dai_link_of(np, priv, i, false);
			if (ret < 0) {
				dev_err(dev,
					"%s: Parsing dai link %d failed(%d)!\n",
					__func__, i, ret);
				of_node_put(np);
				return ret;
			}
			i++;
		}
	} else {
		/* For single DAI link & old style of DT node */
		ret = asoc_sprd_card_dai_link_of(node, priv, 0, true);
		if (ret < 0)
			return ret;
	}
	priv->gpio_hp_det = of_get_named_gpio_flags(node,
						    "sprd-audio-card,hp-det-gpio",
						    0, &flags);
	priv->gpio_hp_det_invert = !!(flags & OF_GPIO_ACTIVE_LOW);
	if (priv->gpio_hp_det == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	priv->gpio_mic_det = of_get_named_gpio_flags(node,
						     "sprd-audio-card,mic-det-gpio",
						     0, &flags);
	priv->gpio_mic_det_invert = !!(flags & OF_GPIO_ACTIVE_LOW);
	if (priv->gpio_mic_det == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	if (priv->gpio_hp_det < 0) {	/* Sprd headset */
		ret = asoc_sprd_card_parse_sprd_headset(node);
		if (ret < 0)
			return ret;
	}
	ret = of_property_read_u32(node, "sprd-audio-card,codec-type", &val);
	if (ret == 0)
		priv->codec_type = val;

	if (!priv->snd_card.name)
		priv->snd_card.name = priv->snd_card.dai_link->name;

	ret = sprd_asoc_card_parse_ext_hook(dev, &priv->ext_hook);
	if (ret < 0)
		return ret;

	return sprd_asoc_card_parse_smartamp_boost(dev, &priv->boost_data);
}

/* Decrease the reference count of the device nodes */
static int asoc_sprd_card_unref(struct snd_soc_card *card)
{
	struct snd_soc_dai_link *dai_link;
	int num_links;

	for (num_links = 0, dai_link = card->dai_link;
	     num_links < card->num_links; num_links++, dai_link++) {
		of_node_put(dai_link->cpu_of_node);
		of_node_put(dai_link->platform_of_node);
		of_node_put(dai_link->codec_of_node);
	}

	return 0;
}

/**
 * asoc_sprd_card_probe - parsing dt config, and fill the struct snd_soc_card
 * accordingly.
 *@pdev: the platform device of the machine driver.
 *@card: the card almost filled completely.
 *
 * You could add some special settings in the respective machine driver.
 */
int asoc_sprd_card_probe(struct platform_device *pdev,
			 struct snd_soc_card **card)
{
	struct sprd_card_data *priv;
	struct snd_soc_dai_link *dai_link;
	struct device_node *np = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	int num_links, ret;

	/* Get the number of DAI links */
	if (np && of_get_child_by_name(np, "sprd-audio-card,dai-link"))
		num_links = of_get_child_count(np);
	else
		num_links = 1;

	/* Allocate the private data and the DAI link array */
	priv = devm_kzalloc(dev,
			    sizeof(*priv) + sizeof(*dai_link) * num_links,
			    GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	/* Init snd_soc_card */
	priv->snd_card.owner = THIS_MODULE;
	priv->snd_card.dev = dev;
	dai_link = priv->dai_link;
	priv->snd_card.dai_link = dai_link;
	priv->snd_card.num_links = num_links;

	priv->gpio_hp_det = -ENOENT;
	priv->gpio_mic_det = -ENOENT;

	/* Get room for the other properties */
	priv->dai_props = devm_kzalloc(dev,
				       sizeof(*priv->dai_props) * num_links,
				       GFP_KERNEL);
	if (!priv->dai_props)
		return -ENOMEM;

	if (np && of_device_is_available(np)) {

		ret = asoc_sprd_card_parse_of(np, priv);
		if (ret < 0) {
			if (ret != -EPROBE_DEFER)
				dev_err(dev, "parse error %d\n", ret);
			goto err;
		}

	} else {
		/* Non-dt way hasn't been presented. */
		pr_err("ERR: %s sound node in dts is not available!\n",
		       __func__);
		ret = -ENODEV;
		goto err;
	}

	snd_soc_card_set_drvdata(&priv->snd_card, priv);

	*card = &priv->snd_card;

	sprd_asoc_ext_hook_register(&priv->ext_hook);

err:
	asoc_sprd_card_unref(&priv->snd_card);

	return ret;
}

int asoc_sprd_card_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);

	return asoc_sprd_card_unref(card);
}

MODULE_ALIAS("platform:asoc-sprd-card");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ASoC SPRD Sound Card Utils");
MODULE_AUTHOR("Peng Lee <peng.lee@spreadtrum.com>");
