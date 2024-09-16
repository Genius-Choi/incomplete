int wvlan_uil(struct uilreq *urq, struct wl_private *lp)
{
	int ioctl_ret = 0;
	/*------------------------------------------------------------------------*/

	DBG_FUNC("wvlan_uil");
	DBG_ENTER(DbgInfo);

	switch (urq->command) {
	case UIL_FUN_CONNECT:
		DBG_TRACE(DbgInfo, "IOCTL: WVLAN2_IOCTL_UIL -- WVLAN2_UIL_CONNECT\n");
		ioctl_ret = wvlan_uil_connect(urq, lp);
		break;
	case UIL_FUN_DISCONNECT:
		DBG_TRACE(DbgInfo, "IOCTL: WVLAN2_IOCTL_UIL -- WVLAN2_UIL_DISCONNECT\n");
		ioctl_ret = wvlan_uil_disconnect(urq, lp);
		break;
	case UIL_FUN_ACTION:
		DBG_TRACE(DbgInfo, "IOCTL: WVLAN2_IOCTL_UIL -- WVLAN2_UIL_ACTION\n");
		ioctl_ret = wvlan_uil_action(urq, lp);
		break;
	case UIL_FUN_SEND_DIAG_MSG:
		DBG_TRACE(DbgInfo, "IOCTL: WVLAN2_IOCTL_UIL -- WVLAN2_UIL_SEND_DIAG_MSG\n");
		ioctl_ret = wvlan_uil_send_diag_msg(urq, lp);
		break;
	case UIL_FUN_GET_INFO:
		DBG_TRACE(DbgInfo, "IOCTL: WVLAN2_IOCTL_UIL -- WVLAN2_UIL_GET_INFO\n");
		ioctl_ret = wvlan_uil_get_info(urq, lp);
		break;
	case UIL_FUN_PUT_INFO:
		DBG_TRACE(DbgInfo, "IOCTL: WVLAN2_IOCTL_UIL -- WVLAN2_UIL_PUT_INFO\n");
		ioctl_ret = wvlan_uil_put_info(urq, lp);
		break;
	default:
		DBG_TRACE(DbgInfo, "IOCTL: WVLAN2_IOCTL_UIL -- UNSUPPORTED UIL CODE: 0x%X", urq->command);
		ioctl_ret = -EOPNOTSUPP;
		break;
	}
	DBG_LEAVE(DbgInfo);
	return ioctl_ret;
} /* wvlan_uil */
