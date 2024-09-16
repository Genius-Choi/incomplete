static u32 ieee80211_idle_on(struct ieee80211_local *local)
{
	if (local->hw.conf.flags & IEEE80211_CONF_IDLE)
		return 0;

#ifdef CONFIG_MAC80211_VERBOSE_DEBUG
	wiphy_debug(local->hw.wiphy, "device now idle\n");
#endif

	drv_flush(local, false);

	local->hw.conf.flags |= IEEE80211_CONF_IDLE;
	return IEEE80211_CONF_CHANGE_IDLE;
}
