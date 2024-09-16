static void hns_xgmac_get_pausefrm_cfg(void *mac_drv, u32 *rx_en, u32 *tx_en)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;
	u32 pause_ctrl;

	pause_ctrl = dsaf_read_dev(drv, XGMAC_MAC_PAUSE_CTRL_REG);
	*rx_en = dsaf_get_bit(pause_ctrl, XGMAC_PAUSE_CTL_RX_B);
	*tx_en = dsaf_get_bit(pause_ctrl, XGMAC_PAUSE_CTL_TX_B);
}
