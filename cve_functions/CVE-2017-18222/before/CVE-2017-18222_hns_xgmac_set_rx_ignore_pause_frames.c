static void hns_xgmac_set_rx_ignore_pause_frames(void *mac_drv, u32 enable)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	dsaf_set_dev_bit(drv, XGMAC_MAC_PAUSE_CTRL_REG,
			 XGMAC_PAUSE_CTL_RX_B, !!enable);
}
