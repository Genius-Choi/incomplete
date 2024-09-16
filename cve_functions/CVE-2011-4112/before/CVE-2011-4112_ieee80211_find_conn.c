ieee80211_find_conn(struct ar6_softc *ar, u8 *node_addr)
{
    sta_t *conn = NULL;
    u8 i, max_conn;

    switch(ar->arNetworkType) {
        case AP_NETWORK:
            max_conn = AP_MAX_NUM_STA;
            break;
        default:
            max_conn=0;
            break;
    }

    for (i = 0; i < max_conn; i++) {
        if (IEEE80211_ADDR_EQ(node_addr, ar->sta_list[i].mac)) {
            conn = &ar->sta_list[i];
            break;
        }
    }

    return conn;
}
