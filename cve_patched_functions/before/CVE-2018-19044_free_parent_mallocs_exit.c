free_parent_mallocs_exit(void)
{
#ifdef _WITH_VRRP_
	if (free_vrrp_pidfile)
		FREE_PTR(vrrp_pidfile);
#endif
#ifdef _WITH_LVS_
	if (free_checkers_pidfile)
		FREE_PTR(checkers_pidfile);
#endif
#ifdef _WITH_BFD_
	if (free_bfd_pidfile)
		FREE_PTR(bfd_pidfile);
#endif

	FREE_PTR(config_id);
}
