static void hns_xgmac_disable(void *mac_drv, enum mac_commom_mode mode)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	if (mode == MAC_COMM_MODE_TX) {
		hns_xgmac_tx_enable(drv, 0);
	} else if (mode == MAC_COMM_MODE_RX) {
		hns_xgmac_rx_enable(drv, 0);
	} else if (mode == MAC_COMM_MODE_RX_AND_TX) {
		hns_xgmac_tx_enable(drv, 0);
		hns_xgmac_rx_enable(drv, 0);
	}
	hns_xgmac_lf_rf_insert(drv, HNS_XGMAC_LF_INSERT);
}
