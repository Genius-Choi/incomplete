static bool nl80211_valid_akm_suite(u32 akm)
{
	return akm == WLAN_AKM_SUITE_8021X ||
		akm == WLAN_AKM_SUITE_PSK;
}
