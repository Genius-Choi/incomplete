int hns_rcb_set_tx_coalesced_frames(
	struct rcb_common_cb *rcb_common, u32 port_idx, u32 coalesced_frames)
{
	u32 old_waterline =
		hns_rcb_get_tx_coalesced_frames(rcb_common, port_idx);
	u64 reg;

	if (coalesced_frames == old_waterline)
		return 0;

	if (coalesced_frames != 1) {
		dev_err(rcb_common->dsaf_dev->dev,
			"error: not support tx coalesce_frames setting!\n");
		return -EINVAL;
	}

	reg = RCB_CFG_PKTLINE_REG + (port_idx + HNS_RCB_TX_PKTLINE_OFFSET) * 4;
	dsaf_write_dev(rcb_common, reg,	coalesced_frames);
	return 0;
}
