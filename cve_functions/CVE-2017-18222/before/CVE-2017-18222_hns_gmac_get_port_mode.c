static void hns_gmac_get_port_mode(void *mac_drv, enum hns_port_mode *port_mode)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	*port_mode = (enum hns_port_mode)dsaf_get_dev_field(
		drv, GMAC_PORT_MODE_REG, GMAC_PORT_MODE_M, GMAC_PORT_MODE_S);
}
