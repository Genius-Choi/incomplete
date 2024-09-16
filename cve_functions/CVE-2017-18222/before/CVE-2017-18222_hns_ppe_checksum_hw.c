static void hns_ppe_checksum_hw(struct hns_ppe_cb *ppe_cb, u32 value)
{
	dsaf_set_dev_field(ppe_cb, PPE_CFG_PRO_CHECK_EN_REG,
			   0xfffffff, 0, value);
}
