static void hns_gmac_config_an_mode(void *mac_drv, u8 newval)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	dsaf_set_dev_bit(drv, GMAC_TRANSMIT_CONTROL_REG,
			 GMAC_TX_AN_EN_B, !!newval);
}
