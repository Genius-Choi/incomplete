static void mac80211_hwsim_sw_scan_complete(struct ieee80211_hw *hw,
					    struct ieee80211_vif *vif)
{
	struct mac80211_hwsim_data *hwsim = hw->priv;

	mutex_lock(&hwsim->mutex);

	pr_debug("hwsim sw_scan_complete\n");
	hwsim->scanning = false;
	eth_zero_addr(hwsim->scan_addr);

	mutex_unlock(&hwsim->mutex);
}
