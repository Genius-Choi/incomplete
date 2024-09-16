static inline bool vif_event_equals(struct brcmf_cfg80211_vif_event *event,
				    u8 action)
{
	u8 evt_action;

	spin_lock(&event->vif_event_lock);
	evt_action = event->action;
	spin_unlock(&event->vif_event_lock);
	return evt_action == action;
}
