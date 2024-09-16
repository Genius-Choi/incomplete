static void hns_ppe_set_port_mode(struct hns_ppe_cb *ppe_cb,
				  enum ppe_port_mode mode)
{
	dsaf_write_dev(ppe_cb, PPE_CFG_XGE_MODE_REG, mode);
}
