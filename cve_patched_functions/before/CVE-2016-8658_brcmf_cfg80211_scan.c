brcmf_cfg80211_scan(struct wiphy *wiphy, struct cfg80211_scan_request *request)
{
	struct brcmf_cfg80211_vif *vif;
	s32 err = 0;

	brcmf_dbg(TRACE, "Enter\n");
	vif = container_of(request->wdev, struct brcmf_cfg80211_vif, wdev);
	if (!check_vif_up(vif))
		return -EIO;

	err = brcmf_cfg80211_escan(wiphy, vif, request, NULL);

	if (err)
		brcmf_err("scan error (%d)\n", err);

	brcmf_dbg(TRACE, "Exit\n");
	return err;
}
