#ifndef __WCN_BUS_H__
#define __WCN_BUS_H__

#define HW_TYPE_SDIO 0
#define HW_TYPE_PCIE 1
#define CHN_MAX_NUM 32
#define PUB_HEAD_RSV 4

struct mbuf_t {
	struct mbuf_t *next;
	unsigned char *buf;
	unsigned long  phy;
	unsigned short len;
	unsigned short rsvd;
	unsigned int   seq;
};

struct mchn_ops_t {
	int channel;
	/* hardware interface type */
	int hif_type;
	/* inout=1 tx side, inout=0 rx side */
	int inout;
	/* set callback pop_link/push_link frequency */
	int intr_interval;
	/* data buffer size */
	int buf_size;
	/* mbuf pool size */
	int pool_size;
	/* The large number of trans */
	int once_max_trans;
	/* rx side threshold */
	int rx_threshold;
	/* tx timeout */
	int timeout;
	/*
	 * pop link list, (1)chn id, (2)mbuf link head
	 * (3) mbuf link tail (4)number of node
	 */
	int (*pop_link)(int, struct mbuf_t *, struct mbuf_t *, int);
	/* ap don't need to implementation */
	int (*push_link)(int, struct mbuf_t **, struct mbuf_t **, int *);
	/* (1)channel id (2)trans time, -1 express timeout */
	int (*tx_complete)(int, int);
};

struct sdio_puh_t {
#ifdef CONFIG_SDIOM
	unsigned int pad:7;
#else
	unsigned int pad:6;
	unsigned int check_sum:1;
#endif
	unsigned int len:16;
	unsigned int eof:1;
	unsigned int subtype:4;
	unsigned int type:4;
}; /* 32bits public header */

struct sprdwcn_bus_ops {
	int (*preinit)(void);
	void (*deinit)(void);

	int (*chn_init)(struct mchn_ops_t *ops);
	int (*chn_deinit)(struct mchn_ops_t *ops);
	int (*list_alloc)(int chn, struct mbuf_t **head,
			  struct mbuf_t **tail, int *num);
	int (*list_free)(int chn, struct mbuf_t *head,
			 struct mbuf_t *tail, int num);
	int (*push_list)(int chn, struct mbuf_t *head,
			 struct mbuf_t *tail, int num);

	/*
	 * for pcie
	 * push link list, Using a blocking mode,
	 * Timeout wait for tx_complete
	 */
	int (*push_link_wait_complete)(int chn, struct mbuf_t *head,
				       struct mbuf_t *tail, int num,
				       int timeout);
	int (*hw_pop_link)(int chn, void *head, void *tail, int num);
	int (*hw_tx_complete)(int chn, int timeout);
	int (*hw_req_push_link)(int chn, int need);

	int (*direct_read)(unsigned int addr, void *buf, unsigned int len);
	int (*direct_write)(unsigned int addr, void *buf, unsigned int len);

	int (*readbyte)(unsigned int addr, unsigned char *val);
	int (*writebyte)(unsigned int addr, unsigned char val);

	unsigned int (*get_carddump_status)(void);
	void (*set_carddump_status)(unsigned int flag);
	unsigned long long (*get_rx_total_cnt)(void);

	int (*rescan)(void);
	void (*register_rescan_cb)(void *);
	void (*remove_card)(void);

	int (*register_pt_rx_process)(unsigned int type,
				unsigned int subtype, void *func);
	int (*register_pt_tx_release)(unsigned int type,
				      unsigned int subtype, void *func);
	int (*pt_write)(void *buf, unsigned int len, unsigned int type,
			    unsigned int subtype);
	int (*pt_read_release)(unsigned int fifo_id);

	int (*driver_register)(void);
	void (*driver_unregister)(void);

};

extern void module_bus_init(void);
extern void module_bus_deinit(void);
extern struct sprdwcn_bus_ops *get_wcn_bus_ops(void);

static inline
int sprdwcn_bus_preinit(void)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->preinit)
		return 0;

	return bus_ops->preinit();
}

static inline
void sprdwcn_bus_deinit(void)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->deinit)
		return;

	return bus_ops->deinit();
}

static inline
int sprdwcn_bus_chn_init(struct mchn_ops_t *ops)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->chn_init)
		return 0;

	return bus_ops->chn_init(ops);
}

static inline
int sprdwcn_bus_chn_deinit(struct mchn_ops_t *ops)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->chn_deinit)
		return 0;

	return bus_ops->chn_deinit(ops);
}

static inline
int sprdwcn_bus_list_alloc(int chn, struct mbuf_t **head,
			   struct mbuf_t **tail, int *num)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->list_alloc)
		return 0;

	return bus_ops->list_alloc(chn, head, tail, num);
}

static inline
int sprdwcn_bus_list_free(int chn, struct mbuf_t *head,
			  struct mbuf_t *tail, int num)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->list_free)
		return 0;

	return bus_ops->list_free(chn, head, tail, num);
}

static inline
int sprdwcn_bus_push_list(int chn, struct mbuf_t *head,
			  struct mbuf_t *tail, int num)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->push_list)
		return 0;

	return bus_ops->push_list(chn, head, tail, num);
}

static inline
int sprdwcn_bus_push_link_wait_complete(int chn, struct mbuf_t *head,
					struct mbuf_t *tail, int num,
					int timeout)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->push_link_wait_complete)
		return 0;

	return bus_ops->push_link_wait_complete(chn, head,
						    tail, num, timeout);
}

static inline
int sprdwcn_bus_hw_pop_link(int chn, void *head, void *tail, int num)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->hw_pop_link)
		return 0;

	return bus_ops->hw_pop_link(chn, head, tail, num);
}

static inline
int sprdwcn_bus_hw_tx_complete(int chn, int timeout)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->hw_tx_complete)
		return 0;

	return bus_ops->hw_tx_complete(chn, timeout);
}

static inline
int sprdwcn_bus_hw_req_push_link(int chn, int need)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->hw_req_push_link)
		return 0;

	return bus_ops->hw_req_push_link(chn, need);
}

static inline
int sprdwcn_bus_direct_read(unsigned int addr,
			    void *buf, unsigned int len)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->direct_read)
		return 0;

	return bus_ops->direct_read(addr, buf, len);
}

static inline
int sprdwcn_bus_direct_write(unsigned int addr,
			     void *buf, unsigned int len)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->direct_write)
		return 0;

	return bus_ops->direct_write(addr, buf, len);
}

static inline
int sprdwcn_bus_aon_readb(unsigned int addr, unsigned char *val)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->readbyte)
		return 0;

	return bus_ops->readbyte(addr, val);
}

static inline
int sprdwcn_bus_aon_writeb(unsigned int addr, unsigned char val)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->writebyte)
		return 0;

	return bus_ops->writebyte(addr, val);
}

static inline
unsigned int sprdwcn_bus_get_carddump_status(void)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->get_carddump_status)
		return 0;

	return bus_ops->get_carddump_status();
}

static inline
void sprdwcn_bus_set_carddump_status(unsigned int flag)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->set_carddump_status)
		return;

	return bus_ops->set_carddump_status(flag);
}

static inline
unsigned long long sprdwcn_bus_get_rx_total_cnt(void)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->get_rx_total_cnt)
		return 0;

	return bus_ops->get_rx_total_cnt();
}

static inline
int sprdwcn_bus_rescan(void)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->rescan)
		return 0;

	return bus_ops->rescan();
}

static inline
void sprdwcn_bus_register_rescan_cb(void *func)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->register_rescan_cb)
		return;

	return bus_ops->register_rescan_cb(func);
}

static inline
void sprdwcn_bus_remove_card(void)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->remove_card)
		return;

	return bus_ops->remove_card();
}

static inline
int sprdwcn_bus_register_pt_rx_process(unsigned int type,
				unsigned int subtype, void *func)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->register_pt_rx_process)
		return 0;

	return bus_ops->register_pt_rx_process(type, subtype, func);
}

static inline
int sprdwcn_bus_register_pt_tx_release(unsigned int type,
				unsigned int subtype, void *func)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->register_pt_tx_release)
		return 0;

	return bus_ops->register_pt_tx_release(type, subtype, func);
}

static inline
int sprdwcn_bus_pt_write(void *buf, unsigned int len,
			 unsigned int type,
			 unsigned int subtype)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->pt_write)
		return 0;

	return bus_ops->pt_write(buf, len, type, subtype);
}

static inline
int sprdwcn_bus_pt_read_release(unsigned int fifo_id)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->pt_read_release)
		return 0;

	return bus_ops->pt_read_release(fifo_id);
}

static inline
int sprdwcn_bus_driver_register(void)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->driver_register)
		return 0;

	return bus_ops->driver_register();
}

static inline
void sprdwcn_bus_driver_unregister(void)
{
	struct sprdwcn_bus_ops *bus_ops = get_wcn_bus_ops();

	if (!bus_ops || !bus_ops->driver_unregister)
		return;

	return bus_ops->driver_unregister();
}

static inline
int wcn_bus_init(void)
{
	module_bus_init();
	return 0;
}

static inline
void wcn_bus_deinit(void)
{
	module_bus_deinit();
}

/* temp for sys module call */
#define mbuf_link_alloc(chn, head, tail, num) \
			sprdwcn_bus_list_alloc(chn, head, tail, num)
#define mbuf_link_free(chn, head, tail, num) \
		       sprdwcn_bus_list_free(chn, head, tail, num)
#define mchn_push_link(chn, head, tail, num) \
		       sprdwcn_bus_push_list(chn, head, tail, num)
#define mchn_init(ops) sprdwcn_bus_chn_init(ops)
#define mchn_deinit(ops) sprdwcn_bus_chn_deinit(ops)

#define mchn_push_link_wait_complete(chn, head, tail, num, timeout) (-1)
#define mchn_hw_pop_link(chn, head, tail, num) do { } while (0)
#define mchn_hw_tx_complete(chn, timeout) do { } while (0)
#define mchn_hw_req_push_link(chn, need) do { } while (0)
#define mchn_ops(channel) NULL
#define mchn_info NULL
#endif

