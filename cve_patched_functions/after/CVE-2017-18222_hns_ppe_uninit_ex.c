void hns_ppe_uninit_ex(struct ppe_common_cb *ppe_common)
{
	u32 i;

	for (i = 0; i < ppe_common->ppe_num; i++) {
		if (ppe_common->dsaf_dev->mac_cb[i])
			hns_ppe_uninit_hw(&ppe_common->ppe_cb[i]);
		memset(&ppe_common->ppe_cb[i], 0, sizeof(struct hns_ppe_cb));
	}
}
