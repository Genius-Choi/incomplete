void ap_wapi_rekey_event(struct ar6_softc *ar, u8 type, u8 *mac)
{
    union iwreq_data wrqu;
    char buf[20];

    A_MEMZERO(buf, sizeof(buf));

    strcpy(buf, "WAPI_REKEY");
    buf[10] = type;
    memcpy(&buf[11], mac, ATH_MAC_LEN);

    A_MEMZERO(&wrqu, sizeof(wrqu));
    wrqu.data.length = 10+1+ATH_MAC_LEN;
    wireless_send_event(ar->arNetDev, IWEVCUSTOM, &wrqu, buf);

    A_PRINTF("WAPI REKEY - %d - %02x:%02x\n", type, mac[4], mac[5]);
}
