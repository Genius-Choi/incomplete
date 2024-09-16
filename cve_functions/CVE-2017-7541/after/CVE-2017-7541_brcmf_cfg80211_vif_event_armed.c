bool brcmf_cfg80211_vif_event_armed(struct brcmf_cfg80211_info *cfg)
{
	struct brcmf_cfg80211_vif_event *event = &cfg->vif_event;
	bool armed;

	spin_lock(&event->vif_event_lock);
	armed = event->vif != NULL;
	spin_unlock(&event->vif_event_lock);

	return armed;
}
