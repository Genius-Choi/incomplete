sta_t *ieee80211_find_conn_for_aid(struct ar6_softc *ar, u8 aid)
{
    sta_t *conn = NULL;
    u8 ctr;

    for (ctr = 0; ctr < AP_MAX_NUM_STA; ctr++) {
        if (ar->sta_list[ctr].aid == aid) {
            conn = &ar->sta_list[ctr];
            break;
        }
    }
    return conn;
}
