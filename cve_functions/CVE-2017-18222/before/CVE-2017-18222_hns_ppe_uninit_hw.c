static void hns_ppe_uninit_hw(struct hns_ppe_cb *ppe_cb)
{
	u32 port;

	if (ppe_cb->ppe_common_cb) {
		struct dsaf_device *dsaf_dev = ppe_cb->ppe_common_cb->dsaf_dev;

		port = ppe_cb->index;
		dsaf_dev->misc_op->ppe_srst(dsaf_dev, port, 0);
	}
}
