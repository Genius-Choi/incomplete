static void hns_gmac_set_tx_auto_pause_frames(void *mac_drv, u16 newval)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	dsaf_set_dev_field(drv, GMAC_FC_TX_TIMER_REG, GMAC_FC_TX_TIMER_M,
			   GMAC_FC_TX_TIMER_S, newval);
}
