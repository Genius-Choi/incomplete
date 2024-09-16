keepalived_running(unsigned long mode)
{
	if (process_running(main_pidfile))
		return true;
#ifdef _WITH_VRRP_
	if (__test_bit(DAEMON_VRRP, &mode) && process_running(vrrp_pidfile))
		return true;
#endif
#ifdef _WITH_LVS_
	if (__test_bit(DAEMON_CHECKERS, &mode) && process_running(checkers_pidfile))
		return true;
#endif
#ifdef _WITH_BFD_
	if (__test_bit(DAEMON_BFD, &mode) && process_running(bfd_pidfile))
		return true;
#endif
	return false;
}
