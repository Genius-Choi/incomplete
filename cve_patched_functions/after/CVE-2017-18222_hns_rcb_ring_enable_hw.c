void hns_rcb_ring_enable_hw(struct hnae_queue *q, u32 val)
{
	dsaf_write_dev(q, RCB_RING_PREFETCH_EN_REG, !!val);
}
