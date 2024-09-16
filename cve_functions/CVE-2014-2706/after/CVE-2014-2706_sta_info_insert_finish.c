static int sta_info_insert_finish(struct sta_info *sta) __acquires(RCU)
{
	struct ieee80211_local *local = sta->local;
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	struct station_info sinfo;
	int err = 0;

	lockdep_assert_held(&local->sta_mtx);

	/* check if STA exists already */
	if (sta_info_get_bss(sdata, sta->sta.addr)) {
		err = -EEXIST;
		goto out_err;
	}

	/* notify driver */
	err = sta_info_insert_drv_state(local, sdata, sta);
	if (err)
		goto out_err;

	local->num_sta++;
	local->sta_generation++;
	smp_mb();

	/* make the station visible */
	sta_info_hash_add(local, sta);

	list_add_rcu(&sta->list, &local->sta_list);

	set_sta_flag(sta, WLAN_STA_INSERTED);

	ieee80211_recalc_min_chandef(sdata);
	ieee80211_sta_debugfs_add(sta);
	rate_control_add_sta_debugfs(sta);

	memset(&sinfo, 0, sizeof(sinfo));
	sinfo.filled = 0;
	sinfo.generation = local->sta_generation;
	cfg80211_new_sta(sdata->dev, sta->sta.addr, &sinfo, GFP_KERNEL);

	sta_dbg(sdata, "Inserted STA %pM\n", sta->sta.addr);

	/* move reference to rcu-protected */
	rcu_read_lock();
	mutex_unlock(&local->sta_mtx);

	if (ieee80211_vif_is_mesh(&sdata->vif))
		mesh_accept_plinks_update(sdata);

	return 0;
 out_err:
	mutex_unlock(&local->sta_mtx);
	rcu_read_lock();
	return err;
}
