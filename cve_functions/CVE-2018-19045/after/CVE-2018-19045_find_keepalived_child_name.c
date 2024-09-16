find_keepalived_child_name(pid_t pid)
{
#ifdef _WITH_LVS_
	if (pid == checkers_child)
		return PROG_CHECK;
#endif
#ifdef _WITH_VRRP_
	if (pid == vrrp_child)
		return PROG_VRRP;
#endif
#ifdef _WITH_BFD_
	if (pid == bfd_child)
		return PROG_BFD;
#endif

	return NULL;
}
