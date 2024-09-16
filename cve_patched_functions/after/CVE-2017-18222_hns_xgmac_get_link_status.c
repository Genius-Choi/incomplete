static void hns_xgmac_get_link_status(void *mac_drv, u32 *link_stat)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	*link_stat = dsaf_read_dev(drv, XGMAC_LINK_STATUS_REG);
}
