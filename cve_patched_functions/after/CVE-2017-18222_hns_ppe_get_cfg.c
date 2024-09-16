static void hns_ppe_get_cfg(struct ppe_common_cb *ppe_common)
{
	u32 i;
	struct hns_ppe_cb *ppe_cb;
	u32 ppe_num = ppe_common->ppe_num;

	for (i = 0; i < ppe_num; i++) {
		ppe_cb = &ppe_common->ppe_cb[i];
		ppe_cb->dev = ppe_common->dev;
		ppe_cb->next = NULL;
		ppe_cb->ppe_common_cb = ppe_common;
		ppe_cb->index = i;
		ppe_cb->io_base = hns_ppe_get_iobase(ppe_common, i);
		ppe_cb->virq = 0;
	}
}
