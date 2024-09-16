static int is_loopback_dst(struct iw_cm_id *cm_id)
{
	struct net_device *dev;
	struct sockaddr_in *raddr = (struct sockaddr_in *)&cm_id->remote_addr;

	dev = ip_dev_find(&init_net, raddr->sin_addr.s_addr);
	if (!dev)
		return 0;
	dev_put(dev);
	return 1;
}
