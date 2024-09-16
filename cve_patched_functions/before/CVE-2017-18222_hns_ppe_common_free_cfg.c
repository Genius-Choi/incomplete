void hns_ppe_common_free_cfg(struct dsaf_device *dsaf_dev, u32 comm_index)
{
	dsaf_dev->ppe_common[comm_index] = NULL;
}
