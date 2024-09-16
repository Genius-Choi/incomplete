static void hns_gmac_config_max_frame_length(void *mac_drv, u16 newval)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	dsaf_set_dev_field(drv, GMAC_MAX_FRM_SIZE_REG, GMAC_MAX_FRM_SIZE_M,
			   GMAC_MAX_FRM_SIZE_S, newval);

	dsaf_set_dev_field(drv, GAMC_RX_MAX_FRAME, GMAC_MAX_FRM_SIZE_M,
			   GMAC_MAX_FRM_SIZE_S, newval);
}
