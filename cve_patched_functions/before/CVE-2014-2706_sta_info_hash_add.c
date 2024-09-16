static void sta_info_hash_add(struct ieee80211_local *local,
			      struct sta_info *sta)
{
	lockdep_assert_held(&local->sta_mtx);
	sta->hnext = local->sta_hash[STA_HASH(sta->sta.addr)];
	rcu_assign_pointer(local->sta_hash[STA_HASH(sta->sta.addr)], sta);
}
