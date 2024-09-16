ar6000_close(struct net_device *dev)
{
    struct ar6_softc    *ar = (struct ar6_softc *)ar6k_priv(dev);
    netif_stop_queue(dev);

    ar6000_disconnect(ar);

    if(ar->arWmiReady == true) {
        if (wmi_scanparams_cmd(ar->arWmi, 0xFFFF, 0,
                               0, 0, 0, 0, 0, 0, 0, 0) != 0) {
            return -EIO;
        }
        ar->arWlanState = WLAN_DISABLED;
    }
	ar6k_cfg80211_scanComplete_event(ar, A_ECANCELED);

    return 0;
}
