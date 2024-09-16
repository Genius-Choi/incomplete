void __iomem *hns_rcb_common_get_vaddr(struct rcb_common_cb *rcb_common)
{
	struct dsaf_device *dsaf_dev = rcb_common->dsaf_dev;

	return dsaf_dev->ppe_base + RCB_COMMON_REG_OFFSET;
}
