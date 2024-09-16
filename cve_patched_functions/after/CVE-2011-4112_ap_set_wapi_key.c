ap_set_wapi_key(struct ar6_softc *ar, void *ikey)
{
    struct ieee80211req_key *ik = (struct ieee80211req_key *)ikey;
    KEY_USAGE   keyUsage = 0;
    int    status;

    if (memcmp(ik->ik_macaddr, bcast_mac, IEEE80211_ADDR_LEN) == 0) {
        keyUsage = GROUP_USAGE;
    } else {
        keyUsage = PAIRWISE_USAGE;
    }
    A_PRINTF("WAPI_KEY: Type:%d ix:%d mac:%02x:%02x len:%d\n",
        keyUsage, ik->ik_keyix, ik->ik_macaddr[4], ik->ik_macaddr[5],
        ik->ik_keylen);

    status = wmi_addKey_cmd(ar->arWmi, ik->ik_keyix, WAPI_CRYPT, keyUsage,
                            ik->ik_keylen, (u8 *)&ik->ik_keyrsc,
                            ik->ik_keydata, KEY_OP_INIT_VAL, ik->ik_macaddr,
                            SYNC_BOTH_WMIFLAG);

    if (0 != status) {
        return -EIO;
    }
    return 0;
}
