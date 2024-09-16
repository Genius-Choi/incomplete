static int __init dcbnl_init(void)
{
	INIT_LIST_HEAD(&dcb_app_list);

	rtnl_register(PF_UNSPEC, RTM_GETDCB, dcb_doit, NULL, NULL);
	rtnl_register(PF_UNSPEC, RTM_SETDCB, dcb_doit, NULL, NULL);

	return 0;
}
