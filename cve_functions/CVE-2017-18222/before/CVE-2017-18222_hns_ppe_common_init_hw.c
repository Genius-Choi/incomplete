static int hns_ppe_common_init_hw(struct ppe_common_cb *ppe_common)
{
	enum ppe_qid_mode qid_mode;
	struct dsaf_device *dsaf_dev = ppe_common->dsaf_dev;
	enum dsaf_mode dsaf_mode = dsaf_dev->dsaf_mode;

	dsaf_dev->misc_op->ppe_comm_srst(dsaf_dev, 0);
	mdelay(100);
	dsaf_dev->misc_op->ppe_comm_srst(dsaf_dev, 1);
	mdelay(100);

	if (ppe_common->ppe_mode == PPE_COMMON_MODE_SERVICE) {
		switch (dsaf_mode) {
		case DSAF_MODE_ENABLE_FIX:
		case DSAF_MODE_DISABLE_FIX:
			qid_mode = PPE_QID_MODE0;
			hns_ppe_set_qid(ppe_common, 0);
			break;
		case DSAF_MODE_ENABLE_0VM:
		case DSAF_MODE_DISABLE_2PORT_64VM:
			qid_mode = PPE_QID_MODE3;
			break;
		case DSAF_MODE_ENABLE_8VM:
		case DSAF_MODE_DISABLE_2PORT_16VM:
			qid_mode = PPE_QID_MODE4;
			break;
		case DSAF_MODE_ENABLE_16VM:
		case DSAF_MODE_DISABLE_6PORT_0VM:
			qid_mode = PPE_QID_MODE5;
			break;
		case DSAF_MODE_ENABLE_32VM:
		case DSAF_MODE_DISABLE_6PORT_16VM:
			qid_mode = PPE_QID_MODE2;
			break;
		case DSAF_MODE_ENABLE_128VM:
		case DSAF_MODE_DISABLE_6PORT_4VM:
			qid_mode = PPE_QID_MODE1;
			break;
		case DSAF_MODE_DISABLE_2PORT_8VM:
			qid_mode = PPE_QID_MODE7;
			break;
		case DSAF_MODE_DISABLE_6PORT_2VM:
			qid_mode = PPE_QID_MODE6;
			break;
		default:
			dev_err(ppe_common->dev,
				"get ppe queue mode failed! dsaf_mode=%d\n",
				dsaf_mode);
			return -EINVAL;
		}
		hns_ppe_set_qid_mode(ppe_common, qid_mode);
	}

	dsaf_set_dev_bit(ppe_common, PPE_COM_COMMON_CNT_CLR_CE_REG,
			 PPE_COMMON_CNT_CLR_CE_B, 1);

	return 0;
}
