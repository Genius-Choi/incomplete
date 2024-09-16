static void hns_gmac_set_promisc(void *mac_drv, u8 en)
{
	struct mac_driver *drv = mac_drv;

	if (drv->mac_cb->mac_type == HNAE_PORT_DEBUG)
		hns_gmac_set_uc_match(mac_drv, en);
}
