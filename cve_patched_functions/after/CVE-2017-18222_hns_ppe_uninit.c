void hns_ppe_uninit(struct dsaf_device *dsaf_dev)
{
	u32 i;

	for (i = 0; i < HNS_PPE_COM_NUM; i++) {
		if (dsaf_dev->ppe_common[i])
			hns_ppe_uninit_ex(dsaf_dev->ppe_common[i]);
		hns_rcb_common_free_cfg(dsaf_dev, i);
		hns_ppe_common_free_cfg(dsaf_dev, i);
	}
}
