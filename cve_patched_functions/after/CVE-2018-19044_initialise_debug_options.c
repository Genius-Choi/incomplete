initialise_debug_options(void)
{
#if defined WITH_DEBUG_OPTIONS && !defined _DEBUG_
	char mask = 0;

	if (prog_type == PROG_TYPE_PARENT)
		mask = 1 << PROG_TYPE_PARENT;
#if _WITH_BFD_
	else if (prog_type == PROG_TYPE_BFD)
		mask = 1 << PROG_TYPE_BFD;
#endif
#if _WITH_LVS_
	else if (prog_type == PROG_TYPE_CHECKER)
		mask = 1 << PROG_TYPE_CHECKER;
#endif
#if _WITH_VRRP_
	else if (prog_type == PROG_TYPE_VRRP)
		mask = 1 << PROG_TYPE_VRRP;
#endif

#ifdef _TIMER_CHECK_
	do_timer_check = !!(timer_debug & mask);
#endif
#ifdef _SMTP_ALERT_DEBUG_
	do_smtp_alert_debug = !!(smtp_debug & mask);
#endif
#ifdef _EPOLL_DEBUG_
	do_epoll_debug = !!(epoll_debug & mask);
#endif
#ifdef _EPOLL_THREAD_DUMP_
	do_epoll_thread_dump = !!(epoll_thread_debug & mask);
#endif
#ifdef _REGEX_DEBUG_
	do_regex_debug = !!(regex_debug & mask);
#endif
#ifdef _WITH_REGEX_TIMERS_
	do_regex_timers = !!(regex_timers & mask);
#endif
#ifdef _TSM_DEBUG_
	do_tsm_debug = !!(tsm_debug & mask);
#endif
#ifdef _VRRP_FD_DEBUG_
	do_vrrp_fd_debug = !!(vrrp_fd_debug & mask);
#endif
#ifdef _NETLINK_TIMERS_
	do_netlink_timers = !!(netlink_timer_debug & mask);
#endif
#endif
}
