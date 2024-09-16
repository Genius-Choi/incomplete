static void hns_ppe_set_vlan_strip(struct hns_ppe_cb *ppe_cb, int en)
{
	dsaf_write_dev(ppe_cb, PPEV2_VLAN_STRIP_EN_REG, en);
}
