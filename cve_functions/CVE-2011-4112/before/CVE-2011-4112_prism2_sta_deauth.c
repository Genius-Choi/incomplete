int prism2_sta_deauth(local_info_t *local, u16 reason)
{
	union iwreq_data wrqu;
	int ret;
	__le16 val = cpu_to_le16(reason);

	if (local->iw_mode != IW_MODE_INFRA ||
	    memcmp(local->bssid, "\x00\x00\x00\x00\x00\x00", ETH_ALEN) == 0 ||
	    memcmp(local->bssid, "\x44\x44\x44\x44\x44\x44", ETH_ALEN) == 0)
		return 0;

	ret = prism2_sta_send_mgmt(local, local->bssid, IEEE80211_STYPE_DEAUTH,
				   (u8 *) &val, 2);
	memset(wrqu.ap_addr.sa_data, 0, ETH_ALEN);
	wireless_send_event(local->dev, SIOCGIWAP, &wrqu, NULL);
	return ret;
}
