ar6000_restart_endpoint(struct net_device *dev)
{
    int status = 0;
    struct ar6_softc *ar = (struct ar6_softc *)ar6k_priv(dev);

    BMIInit();
    do {
        if ( (status=ar6000_configure_target(ar))!= 0)
            break;
        if ( (status=ar6000_sysfs_bmi_get_config(ar, wlaninitmode)) != 0)
        {
            AR_DEBUG_PRINTF(ATH_DEBUG_ERR,("ar6000_avail: ar6000_sysfs_bmi_get_config failed\n"));
            break;
        }
        rtnl_lock();
        status = (ar6000_init(dev)==0) ? 0 : A_ERROR;
        rtnl_unlock();

        if (status) {
            break;
        }
        if (ar->arSsidLen && ar->arWlanState == WLAN_ENABLED) {
            ar6000_connect_to_ap(ar);
        }  
    } while (0);

    if (status== 0) {
        return;
    }

    ar6000_devices[ar->arDeviceIndex] = NULL;
    ar6000_destroy(ar->arNetDev, 1);
}
