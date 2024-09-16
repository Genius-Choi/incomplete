static void hns_xgmac_set_pausefrm_mac_addr(void *mac_drv, char *mac_addr)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	u32 high_val = mac_addr[1] | (mac_addr[0] << 8);
	u32 low_val = mac_addr[5] | (mac_addr[4] << 8)
		| (mac_addr[3] << 16) | (mac_addr[2] << 24);
	dsaf_write_dev(drv, XGMAC_MAC_PAUSE_LOCAL_MAC_L_REG, low_val);
	dsaf_write_dev(drv, XGMAC_MAC_PAUSE_LOCAL_MAC_H_REG, high_val);
}
