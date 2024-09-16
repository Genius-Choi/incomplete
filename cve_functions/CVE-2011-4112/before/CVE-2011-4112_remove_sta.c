u8 remove_sta(struct ar6_softc *ar, u8 *mac, u16 reason)
{
    u8 i, removed=0;

    if(IS_MAC_NULL(mac)) {
        return removed;
    }

    if(IS_MAC_BCAST(mac)) {
        A_PRINTF("DEL ALL STA\n");
        for(i=0; i < AP_MAX_NUM_STA; i++) {
            if(!IS_MAC_NULL(ar->sta_list[i].mac)) {
                sta_cleanup(ar, i);
                removed = 1;
            }
        }
    } else {
        for(i=0; i < AP_MAX_NUM_STA; i++) {
            if(memcmp(ar->sta_list[i].mac, mac, ATH_MAC_LEN)==0) {
                A_PRINTF("DEL STA %2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x "
                " aid=%d REASON=%d\n", mac[0], mac[1], mac[2],
                 mac[3], mac[4], mac[5], ar->sta_list[i].aid, reason);

                sta_cleanup(ar, i);
                removed = 1;
                break;
            }
        }
    }
    return removed;
}
