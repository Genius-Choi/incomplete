static void hns_rcb_set_port_timeout(
	struct rcb_common_cb *rcb_common, u32 port_idx, u32 timeout)
{
	if (AE_IS_VER1(rcb_common->dsaf_dev->dsaf_ver)) {
		dsaf_write_dev(rcb_common, RCB_CFG_OVERTIME_REG,
			       timeout * HNS_RCB_CLK_FREQ_MHZ);
	} else if (!HNS_DSAF_IS_DEBUG(rcb_common->dsaf_dev)) {
		if (timeout > HNS_RCB_DEF_GAP_TIME_USECS)
			dsaf_write_dev(rcb_common,
				       RCB_PORT_INT_GAPTIME_REG + port_idx * 4,
				       HNS_RCB_DEF_GAP_TIME_USECS);
		else
			dsaf_write_dev(rcb_common,
				       RCB_PORT_INT_GAPTIME_REG + port_idx * 4,
				       timeout);

		dsaf_write_dev(rcb_common,
			       RCB_PORT_CFG_OVERTIME_REG + port_idx * 4,
			       timeout);
	} else {
		dsaf_write_dev(rcb_common,
			       RCB_PORT_CFG_OVERTIME_REG + port_idx * 4,
			       timeout);
	}
}
