ar6000_ap_mode_get_wpa_ie(struct ar6_softc *ar, struct ieee80211req_wpaie *wpaie)
{
    sta_t *conn = NULL;
    conn = ieee80211_find_conn(ar, wpaie->wpa_macaddr);

    A_MEMZERO(wpaie->wpa_ie, IEEE80211_MAX_IE);
    A_MEMZERO(wpaie->rsn_ie, IEEE80211_MAX_IE);

    if(conn) {
        memcpy(wpaie->wpa_ie, conn->wpa_ie, IEEE80211_MAX_IE);
    }

    return 0;
}
