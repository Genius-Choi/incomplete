int hns_rcb_set_rx_coalesced_frames(
	struct rcb_common_cb *rcb_common, u32 port_idx, u32 coalesced_frames)
{
	u32 old_waterline =
		hns_rcb_get_rx_coalesced_frames(rcb_common, port_idx);

	if (coalesced_frames == old_waterline)
		return 0;

	if (coalesced_frames >= rcb_common->desc_num ||
	    coalesced_frames > HNS_RCB_MAX_COALESCED_FRAMES ||
	    coalesced_frames < HNS_RCB_MIN_COALESCED_FRAMES) {
		dev_err(rcb_common->dsaf_dev->dev,
			"error: not support coalesce_frames setting!\n");
		return -EINVAL;
	}

	dsaf_write_dev(rcb_common, RCB_CFG_PKTLINE_REG + port_idx * 4,
		       coalesced_frames);
	return 0;
}
