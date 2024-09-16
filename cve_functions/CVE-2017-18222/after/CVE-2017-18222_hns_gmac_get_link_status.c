static void hns_gmac_get_link_status(void *mac_drv, u32 *link_stat)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	*link_stat = dsaf_get_dev_bit(drv, GMAC_AN_NEG_STATE_REG,
				      GMAC_AN_NEG_STAT_RX_SYNC_OK_B);
}
