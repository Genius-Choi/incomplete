set_debug_options(const char *options)
{
	char all_processes, processes;
	char opt;
	const char *opt_p = options;

#ifdef _DEBUG_
	all_processes = 1;
#else
	all_processes = (1 << PROG_TYPE_PARENT);
#if _WITH_BFD_
	all_processes |= (1 << PROG_TYPE_BFD);
#endif
#if _WITH_LVS_
	all_processes |= (1 << PROG_TYPE_CHECKER);
#endif
#if _WITH_VRRP_
	all_processes |= (1 << PROG_TYPE_VRRP);
#endif
#endif

	if (!options) {
#ifdef _TIMER_CHECK_
		timer_debug = all_processes;
#endif
#ifdef _SMTP_ALERT_DEBUG_
		smtp_debug = all_processes;
#endif
#ifdef _EPOLL_DEBUG_
		epoll_debug = all_processes;
#endif
#ifdef _EPOLL_THREAD_DUMP_
		epoll_thread_debug = all_processes;
#endif
#ifdef _REGEX_DEBUG_
		regex_debug = all_processes;
#endif
#ifdef _WITH_REGEX_TIMERS_
		regex_timers = all_processes;
#endif
#ifdef _TSM_DEBUG_
		tsm_debug = all_processes;
#endif
#ifdef _VRRP_FD_DEBUG_
		vrrp_fd_debug = all_processes;
#endif
#ifdef _NETLINK_TIMERS_
		netlink_timer_debug = all_processes;
#endif

		return;
	}

	opt_p = options;
	do {
		if (!isupper(*opt_p)) {
			fprintf(stderr, "Unknown debug option'%c' in '%s'\n", *opt_p, options);
			return;
		}
		opt = *opt_p++;

#ifdef _DEBUG_
		processes = all_processes;
#else
		if (!*opt_p || isupper(*opt_p))
			processes = all_processes;
		else {
			processes = 0;
			while (*opt_p && !isupper(*opt_p)) {
				switch (*opt_p) {
				case 'p':
					processes |= (1 << PROG_TYPE_PARENT);
					break;
#if _WITH_BFD_
				case 'b':
					processes |= (1 << PROG_TYPE_BFD);
					break;
#endif
#if _WITH_LVS_
				case 'c':
					processes |= (1 << PROG_TYPE_CHECKER);
					break;
#endif
#if _WITH_VRRP_
				case 'v':
					processes |= (1 << PROG_TYPE_VRRP);
					break;
#endif
				default:
					fprintf(stderr, "Unknown debug process '%c' in '%s'\n", *opt_p, options);
					return;
				}
				opt_p++;
			}
		}
#endif

		switch (opt) {
#ifdef _TIMER_CHECK_
		case 'T':
			timer_debug = processes;
			break;
#endif
#ifdef _SMTP_ALERT_DEBUG_
		case 'M':
			smtp_debug = processes;
			break;
#endif
#ifdef _EPOLL_DEBUG_
		case 'E':
			epoll_debug = processes;
			break;
#endif
#ifdef _EPOLL_THREAD_DUMP_
		case 'D':
			epoll_thread_debug = processes;
			break;
#endif
#ifdef _REGEX_DEBUG_
		case 'R':
			regex_debug = processes;
			break;
#endif
#ifdef _WITH_REGEX_TIMERS_
		case 'X':
			regex_timers = processes;
			break;
#endif
#ifdef _TSM_DEBUG_
		case 'S':
			tsm_debug = processes;
			break;
#endif
#ifdef _VRRP_FD_DEBUG_
		case 'F':
			vrrp_fd_debug = processes;
			break;
#endif
#ifdef _NETLINK_TIMERS_
		case 'N':
			netlink_timer_debug = processes;
			break;
#endif
		default:
			fprintf(stderr, "Unknown debug type '%c' in '%s'\n", opt, options);
			return;
		}
	} while (opt_p && *opt_p);
}
