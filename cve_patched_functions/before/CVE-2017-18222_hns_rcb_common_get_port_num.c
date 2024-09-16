static int hns_rcb_common_get_port_num(struct rcb_common_cb *rcb_common)
{
	if (!HNS_DSAF_IS_DEBUG(rcb_common->dsaf_dev))
		return HNS_RCB_SERVICE_NW_ENGINE_NUM;
	else
		return HNS_RCB_DEBUG_NW_ENGINE_NUM;
}
