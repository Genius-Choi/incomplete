ar6000_scanComplete_event(struct ar6_softc *ar, int status)
{

    ar6k_cfg80211_scanComplete_event(ar, status);

    if (!ar->arUserBssFilter) {
        wmi_bssfilter_cmd(ar->arWmi, NONE_BSS_FILTER, 0);
    }
    if (ar->scan_triggered) {
        if (status== 0) {
            union iwreq_data wrqu;
            A_MEMZERO(&wrqu, sizeof(wrqu));
            wireless_send_event(ar->arNetDev, SIOCGIWSCAN, &wrqu, NULL);
        }
        ar->scan_triggered = 0;
    }

    AR_DEBUG_PRINTF(ATH_DEBUG_WLAN_SCAN,( "AR6000 scan complete: %d\n", status));
}
