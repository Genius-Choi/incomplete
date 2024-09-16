static void __exit dcbnl_exit(void)
{
	rtnl_unregister(PF_UNSPEC, RTM_GETDCB);
	rtnl_unregister(PF_UNSPEC, RTM_SETDCB);
	dcb_flushapp();
}
