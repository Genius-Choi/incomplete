static void mac80211_hwsim_remove_interface(
	struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	wiphy_dbg(hw->wiphy, "%s (type=%d mac_addr=%pM)\n",
		  __func__, ieee80211_vif_type_p2p(vif),
		  vif->addr);
	hwsim_check_magic(vif);
	hwsim_clear_magic(vif);
}
