static void ieee80211_update_csa(struct ieee80211_sub_if_data *sdata,
				 struct beacon_data *beacon)
{
	struct probe_resp *resp;
	int counter_offset_beacon = sdata->csa_counter_offset_beacon;
	int counter_offset_presp = sdata->csa_counter_offset_presp;
	u8 *beacon_data;
	size_t beacon_data_len;

	switch (sdata->vif.type) {
	case NL80211_IFTYPE_AP:
		beacon_data = beacon->tail;
		beacon_data_len = beacon->tail_len;
		break;
	case NL80211_IFTYPE_ADHOC:
		beacon_data = beacon->head;
		beacon_data_len = beacon->head_len;
		break;
	case NL80211_IFTYPE_MESH_POINT:
		beacon_data = beacon->head;
		beacon_data_len = beacon->head_len;
		break;
	default:
		return;
	}
	if (WARN_ON(counter_offset_beacon >= beacon_data_len))
		return;

	/* warn if the driver did not check for/react to csa completeness */
	if (WARN_ON(beacon_data[counter_offset_beacon] == 0))
		return;

	beacon_data[counter_offset_beacon]--;

	if (sdata->vif.type == NL80211_IFTYPE_AP && counter_offset_presp) {
		rcu_read_lock();
		resp = rcu_dereference(sdata->u.ap.probe_resp);

		/* if nl80211 accepted the offset, this should not happen. */
		if (WARN_ON(!resp)) {
			rcu_read_unlock();
			return;
		}
		resp->data[counter_offset_presp]--;
		rcu_read_unlock();
	}
}
