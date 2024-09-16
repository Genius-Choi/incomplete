u32 hns_rcb_get_coalesce_usecs(
	struct rcb_common_cb *rcb_common, u32 port_idx)
{
	if (AE_IS_VER1(rcb_common->dsaf_dev->dsaf_ver))
		return dsaf_read_dev(rcb_common, RCB_CFG_OVERTIME_REG) /
		       HNS_RCB_CLK_FREQ_MHZ;
	else
		return dsaf_read_dev(rcb_common,
				     RCB_PORT_CFG_OVERTIME_REG + port_idx * 4);
}
