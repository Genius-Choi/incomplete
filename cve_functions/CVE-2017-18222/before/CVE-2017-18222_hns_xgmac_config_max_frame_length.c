static void hns_xgmac_config_max_frame_length(void *mac_drv, u16 newval)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	dsaf_write_dev(drv, XGMAC_MAC_MAX_PKT_SIZE_REG, newval);
}
