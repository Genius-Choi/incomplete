static void hns_gmac_autoneg_stat(void *mac_drv, u32 *enable)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	*enable = dsaf_get_dev_bit(drv, GMAC_TRANSMIT_CONTROL_REG,
				   GMAC_TX_AN_EN_B);
}
