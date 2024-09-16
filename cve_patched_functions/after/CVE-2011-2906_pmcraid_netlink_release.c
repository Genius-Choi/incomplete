static void pmcraid_netlink_release(void)
{
	genl_unregister_family(&pmcraid_event_family);
}
