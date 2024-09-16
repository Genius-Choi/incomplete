u32 hns_rcb_get_tx_coalesced_frames(
	struct rcb_common_cb *rcb_common, u32 port_idx)
{
	u64 reg;

	reg = RCB_CFG_PKTLINE_REG + (port_idx + HNS_RCB_TX_PKTLINE_OFFSET) * 4;
	return dsaf_read_dev(rcb_common, reg);
}
