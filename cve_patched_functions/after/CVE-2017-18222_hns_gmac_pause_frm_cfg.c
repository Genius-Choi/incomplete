static void hns_gmac_pause_frm_cfg(void *mac_drv, u32 rx_pause_en,
				   u32 tx_pause_en)
{
	u32 pause_en;
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	pause_en = dsaf_read_dev(drv, GMAC_PAUSE_EN_REG);
	dsaf_set_bit(pause_en, GMAC_PAUSE_EN_RX_FDFC_B, !!rx_pause_en);
	dsaf_set_bit(pause_en, GMAC_PAUSE_EN_TX_FDFC_B, !!tx_pause_en);
	dsaf_write_dev(drv, GMAC_PAUSE_EN_REG, pause_en);
}
