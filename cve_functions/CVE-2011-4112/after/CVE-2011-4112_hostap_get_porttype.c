u16 hostap_get_porttype(local_info_t *local)
{
	if (local->iw_mode == IW_MODE_ADHOC && local->pseudo_adhoc)
		return HFA384X_PORTTYPE_PSEUDO_IBSS;
	if (local->iw_mode == IW_MODE_ADHOC)
		return HFA384X_PORTTYPE_IBSS;
	if (local->iw_mode == IW_MODE_INFRA)
		return HFA384X_PORTTYPE_BSS;
	if (local->iw_mode == IW_MODE_REPEAT)
		return HFA384X_PORTTYPE_WDS;
	if (local->iw_mode == IW_MODE_MONITOR)
		return HFA384X_PORTTYPE_PSEUDO_IBSS;
	return HFA384X_PORTTYPE_HOSTAP;
}
