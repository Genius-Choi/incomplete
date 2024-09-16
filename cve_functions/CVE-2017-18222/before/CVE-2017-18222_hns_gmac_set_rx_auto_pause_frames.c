static void hns_gmac_set_rx_auto_pause_frames(void *mac_drv, u32 newval)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	dsaf_set_dev_bit(drv, GMAC_PAUSE_EN_REG,
			 GMAC_PAUSE_EN_RX_FDFC_B, !!newval);
}
