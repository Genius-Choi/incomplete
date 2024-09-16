hns_ppe_common_get_ioaddr(struct ppe_common_cb *ppe_common)
{
	return ppe_common->dsaf_dev->ppe_base + PPE_COMMON_REG_OFFSET;
}
