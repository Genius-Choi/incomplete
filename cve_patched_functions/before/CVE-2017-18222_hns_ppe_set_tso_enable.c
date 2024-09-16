void hns_ppe_set_tso_enable(struct hns_ppe_cb *ppe_cb, u32 value)
{
	dsaf_set_dev_bit(ppe_cb, PPEV2_CFG_TSO_EN_REG, 0, !!value);
}
