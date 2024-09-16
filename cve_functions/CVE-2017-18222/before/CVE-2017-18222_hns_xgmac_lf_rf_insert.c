static void hns_xgmac_lf_rf_insert(struct mac_driver *mac_drv, u32 mode)
{
	dsaf_set_dev_field(mac_drv, XGMAC_MAC_TX_LF_RF_CONTROL_REG,
			   XGMAC_LF_RF_INSERT_M, XGMAC_LF_RF_INSERT_S, mode);
}
