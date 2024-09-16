static void clear_sta_ps_flags(void *_sta)
{
	struct sta_info *sta = _sta;
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	struct ps_data *ps;

	if (sdata->vif.type == NL80211_IFTYPE_AP ||
	    sdata->vif.type == NL80211_IFTYPE_AP_VLAN)
		ps = &sdata->bss->ps;
	else if (ieee80211_vif_is_mesh(&sdata->vif))
		ps = &sdata->u.mesh.ps;
	else
		return;

	clear_sta_flag(sta, WLAN_STA_PS_DRIVER);
	if (test_and_clear_sta_flag(sta, WLAN_STA_PS_STA))
		atomic_dec(&ps->num_sta_ps);
}
