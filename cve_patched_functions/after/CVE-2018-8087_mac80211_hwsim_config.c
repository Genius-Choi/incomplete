static int mac80211_hwsim_config(struct ieee80211_hw *hw, u32 changed)
{
	struct mac80211_hwsim_data *data = hw->priv;
	struct ieee80211_conf *conf = &hw->conf;
	static const char *smps_modes[IEEE80211_SMPS_NUM_MODES] = {
		[IEEE80211_SMPS_AUTOMATIC] = "auto",
		[IEEE80211_SMPS_OFF] = "off",
		[IEEE80211_SMPS_STATIC] = "static",
		[IEEE80211_SMPS_DYNAMIC] = "dynamic",
	};
	int idx;

	if (conf->chandef.chan)
		wiphy_dbg(hw->wiphy,
			  "%s (freq=%d(%d - %d)/%s idle=%d ps=%d smps=%s)\n",
			  __func__,
			  conf->chandef.chan->center_freq,
			  conf->chandef.center_freq1,
			  conf->chandef.center_freq2,
			  hwsim_chanwidths[conf->chandef.width],
			  !!(conf->flags & IEEE80211_CONF_IDLE),
			  !!(conf->flags & IEEE80211_CONF_PS),
			  smps_modes[conf->smps_mode]);
	else
		wiphy_dbg(hw->wiphy,
			  "%s (freq=0 idle=%d ps=%d smps=%s)\n",
			  __func__,
			  !!(conf->flags & IEEE80211_CONF_IDLE),
			  !!(conf->flags & IEEE80211_CONF_PS),
			  smps_modes[conf->smps_mode]);

	data->idle = !!(conf->flags & IEEE80211_CONF_IDLE);

	WARN_ON(conf->chandef.chan && data->use_chanctx);

	mutex_lock(&data->mutex);
	if (data->scanning && conf->chandef.chan) {
		for (idx = 0; idx < ARRAY_SIZE(data->survey_data); idx++) {
			if (data->survey_data[idx].channel == data->channel) {
				data->survey_data[idx].start =
					data->survey_data[idx].next_start;
				data->survey_data[idx].end = jiffies;
				break;
			}
		}

		data->channel = conf->chandef.chan;

		for (idx = 0; idx < ARRAY_SIZE(data->survey_data); idx++) {
			if (data->survey_data[idx].channel &&
			    data->survey_data[idx].channel != data->channel)
				continue;
			data->survey_data[idx].channel = data->channel;
			data->survey_data[idx].next_start = jiffies;
			break;
		}
	} else {
		data->channel = conf->chandef.chan;
	}
	mutex_unlock(&data->mutex);

	if (!data->started || !data->beacon_int)
		tasklet_hrtimer_cancel(&data->beacon_timer);
	else if (!hrtimer_is_queued(&data->beacon_timer.timer)) {
		u64 tsf = mac80211_hwsim_get_tsf(hw, NULL);
		u32 bcn_int = data->beacon_int;
		u64 until_tbtt = bcn_int - do_div(tsf, bcn_int);

		tasklet_hrtimer_start(&data->beacon_timer,
				      ns_to_ktime(until_tbtt * 1000),
				      HRTIMER_MODE_REL);
	}

	return 0;
}
