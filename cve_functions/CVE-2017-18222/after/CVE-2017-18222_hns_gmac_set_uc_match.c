static void hns_gmac_set_uc_match(void *mac_drv, u16 en)
{
	struct mac_driver *drv = mac_drv;

	dsaf_set_dev_bit(drv, GMAC_REC_FILT_CONTROL_REG,
			 GMAC_UC_MATCH_EN_B, !en);
	dsaf_set_dev_bit(drv, GMAC_STATION_ADDR_HIGH_2_REG,
			 GMAC_ADDR_EN_B, !en);
}
