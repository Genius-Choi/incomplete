static phys_addr_t hns_rcb_common_get_paddr(struct rcb_common_cb *rcb_common)
{
	struct dsaf_device *dsaf_dev = rcb_common->dsaf_dev;

	return dsaf_dev->ppe_paddr + RCB_COMMON_REG_OFFSET;
}
