static int hns_rcb_get_base_irq_idx(struct rcb_common_cb *rcb_common)
{
	bool is_ver1 = AE_IS_VER1(rcb_common->dsaf_dev->dsaf_ver);

	if (!HNS_DSAF_IS_DEBUG(rcb_common->dsaf_dev))
		return SERVICE_RING_IRQ_IDX(is_ver1);
	else
		return  HNS_DEBUG_RING_IRQ_IDX;
}
