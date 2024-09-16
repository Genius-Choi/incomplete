static int ath6kl_init_netdev(struct ar6_softc *ar)
{
	int r;

        r = ar6000_sysfs_bmi_get_config(ar, wlaninitmode);
        if (r) {
		AR_DEBUG_PRINTF(ATH_DEBUG_ERR,
				("ar6000_avail: "
				 "ar6000_sysfs_bmi_get_config failed\n"));
		return r;
        }

	return ath6kl_init_netdev_wmi(ar->arNetDev);
}
