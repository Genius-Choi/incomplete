static bool nl80211_valid_cipher_suite(u32 cipher)
{
	return cipher == WLAN_CIPHER_SUITE_WEP40 ||
		cipher == WLAN_CIPHER_SUITE_WEP104 ||
		cipher == WLAN_CIPHER_SUITE_TKIP ||
		cipher == WLAN_CIPHER_SUITE_CCMP ||
		cipher == WLAN_CIPHER_SUITE_AES_CMAC;
}
