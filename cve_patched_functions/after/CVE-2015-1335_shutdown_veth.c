static int shutdown_veth(struct lxc_handler *handler, struct lxc_netdev *netdev)
{
	char *veth1;
	int err;

	if (netdev->priv.veth_attr.pair)
		veth1 = netdev->priv.veth_attr.pair;
	else
		veth1 = netdev->priv.veth_attr.veth1;

	if (netdev->downscript) {
		err = run_script(handler->name, "net", netdev->downscript,
				 "down", "veth", veth1, (char*) NULL);
		if (err)
			return -1;
	}
	return 0;
}
