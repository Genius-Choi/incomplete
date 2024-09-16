static void hns_gmac_get_duplex_type(void *mac_drv,
				     enum hns_gmac_duplex_mdoe *duplex_mode)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	*duplex_mode = (enum hns_gmac_duplex_mdoe)dsaf_get_dev_bit(
		drv, GMAC_DUPLEX_TYPE_REG, GMAC_DUPLEX_TYPE_B);
}
