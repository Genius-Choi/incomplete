static int shutdown_macvlan(struct lxc_handler *handler, struct lxc_netdev *netdev)
{
	int err;

	if (netdev->downscript) {
		err = run_script(handler->name, "net", netdev->downscript,
				 "down", "macvlan", netdev->link,
				 (char*) NULL);
		if (err)
			return -1;
	}
	return 0;
}
