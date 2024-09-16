ar6000_reinstall_keys(struct ar6_softc *ar, u8 key_op_ctrl)
{
    int status = 0;
    struct ieee80211req_key *uik = &ar->user_saved_keys.ucast_ik;
    struct ieee80211req_key *bik = &ar->user_saved_keys.bcast_ik;
    CRYPTO_TYPE  keyType = ar->user_saved_keys.keyType;

    if (IEEE80211_CIPHER_CCKM_KRK != uik->ik_type) {
        if (NONE_CRYPT == keyType) {
            goto _reinstall_keys_out;
        }

        if (uik->ik_keylen) {
            status = wmi_addKey_cmd(ar->arWmi, uik->ik_keyix,
                    ar->user_saved_keys.keyType, PAIRWISE_USAGE,
                    uik->ik_keylen, (u8 *)&uik->ik_keyrsc,
                    uik->ik_keydata, key_op_ctrl, uik->ik_macaddr, SYNC_BEFORE_WMIFLAG);
        }

    } else {
        status = wmi_add_krk_cmd(ar->arWmi, uik->ik_keydata);
    }

    if (IEEE80211_CIPHER_CCKM_KRK != bik->ik_type) {
        if (NONE_CRYPT == keyType) {
            goto _reinstall_keys_out;
        }

        if (bik->ik_keylen) {
            status = wmi_addKey_cmd(ar->arWmi, bik->ik_keyix,
                    ar->user_saved_keys.keyType, GROUP_USAGE,
                    bik->ik_keylen, (u8 *)&bik->ik_keyrsc,
                    bik->ik_keydata, key_op_ctrl, bik->ik_macaddr, NO_SYNC_WMIFLAG);
        }
    } else {
        status = wmi_add_krk_cmd(ar->arWmi, bik->ik_keydata);
    }

_reinstall_keys_out:
    ar->user_savedkeys_stat = USER_SAVEDKEYS_STAT_INIT;
    ar->user_key_ctrl      = 0;

    return status;
}
