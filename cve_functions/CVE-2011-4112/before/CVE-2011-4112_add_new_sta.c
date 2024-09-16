add_new_sta(struct ar6_softc *ar, u8 *mac, u16 aid, u8 *wpaie,
            u8 ielen, u8 keymgmt, u8 ucipher, u8 auth)
{
    u8 free_slot=aid-1;

        memcpy(ar->sta_list[free_slot].mac, mac, ATH_MAC_LEN);
        memcpy(ar->sta_list[free_slot].wpa_ie, wpaie, ielen);
        ar->sta_list[free_slot].aid = aid;
        ar->sta_list[free_slot].keymgmt = keymgmt;
        ar->sta_list[free_slot].ucipher = ucipher;
        ar->sta_list[free_slot].auth = auth;
        ar->sta_list_index = ar->sta_list_index | (1 << free_slot);
    ar->arAPStats.sta[free_slot].aid = aid;
}
