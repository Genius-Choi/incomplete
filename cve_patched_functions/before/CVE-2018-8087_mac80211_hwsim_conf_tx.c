static int mac80211_hwsim_conf_tx(
	struct ieee80211_hw *hw,
	struct ieee80211_vif *vif, u16 queue,
	const struct ieee80211_tx_queue_params *params)
{
	wiphy_dbg(hw->wiphy,
		  "%s (queue=%d txop=%d cw_min=%d cw_max=%d aifs=%d)\n",
		  __func__, queue,
		  params->txop, params->cw_min,
		  params->cw_max, params->aifs);
	return 0;
}
