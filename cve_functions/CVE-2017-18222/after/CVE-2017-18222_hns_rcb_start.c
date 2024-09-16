void hns_rcb_start(struct hnae_queue *q, u32 val)
{
	hns_rcb_ring_enable_hw(q, val);
}
