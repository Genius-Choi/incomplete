brcmf_config_ap_mgmt_ie(struct brcmf_cfg80211_vif *vif,
			struct cfg80211_beacon_data *beacon)
{
	s32 err;

	/* Set Beacon IEs to FW */
	err = brcmf_vif_set_mgmt_ie(vif, BRCMF_VNDR_IE_BEACON_FLAG,
				    beacon->tail, beacon->tail_len);
	if (err) {
		brcmf_err("Set Beacon IE Failed\n");
		return err;
	}
	brcmf_dbg(TRACE, "Applied Vndr IEs for Beacon\n");

	/* Set Probe Response IEs to FW */
	err = brcmf_vif_set_mgmt_ie(vif, BRCMF_VNDR_IE_PRBRSP_FLAG,
				    beacon->proberesp_ies,
				    beacon->proberesp_ies_len);
	if (err)
		brcmf_err("Set Probe Resp IE Failed\n");
	else
		brcmf_dbg(TRACE, "Applied Vndr IEs for Probe Resp\n");

	return err;
}
