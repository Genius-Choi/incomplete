int hns_ppe_common_get_cfg(struct dsaf_device *dsaf_dev, int comm_index)
{
	struct ppe_common_cb *ppe_common;
	int ppe_num;

	if (!HNS_DSAF_IS_DEBUG(dsaf_dev))
		ppe_num = HNS_PPE_SERVICE_NW_ENGINE_NUM;
	else
		ppe_num = HNS_PPE_DEBUG_NW_ENGINE_NUM;

	ppe_common = devm_kzalloc(dsaf_dev->dev, sizeof(*ppe_common) +
		ppe_num * sizeof(struct hns_ppe_cb), GFP_KERNEL);
	if (!ppe_common)
		return -ENOMEM;

	ppe_common->ppe_num = ppe_num;
	ppe_common->dsaf_dev = dsaf_dev;
	ppe_common->comm_index = comm_index;
	if (!HNS_DSAF_IS_DEBUG(dsaf_dev))
		ppe_common->ppe_mode = PPE_COMMON_MODE_SERVICE;
	else
		ppe_common->ppe_mode = PPE_COMMON_MODE_DEBUG;
	ppe_common->dev = dsaf_dev->dev;

	ppe_common->io_base = hns_ppe_common_get_ioaddr(ppe_common);

	dsaf_dev->ppe_common[comm_index] = ppe_common;

	return 0;
}
