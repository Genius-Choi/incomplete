static void hns_xgmac_lf_rf_control_init(struct mac_driver *mac_drv)
{
	u32 val = 0;

	dsaf_set_bit(val, XGMAC_UNIDIR_EN_B, 0);
	dsaf_set_bit(val, XGMAC_RF_TX_EN_B, 1);
	dsaf_set_field(val, XGMAC_LF_RF_INSERT_M, XGMAC_LF_RF_INSERT_S, 0);
	dsaf_write_reg(mac_drv, XGMAC_MAC_TX_LF_RF_CONTROL_REG, val);
}
