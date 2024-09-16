u32 hns_rcb_get_rx_coalesced_frames(
	struct rcb_common_cb *rcb_common, u32 port_idx)
{
	return dsaf_read_dev(rcb_common, RCB_CFG_PKTLINE_REG + port_idx * 4);
}
