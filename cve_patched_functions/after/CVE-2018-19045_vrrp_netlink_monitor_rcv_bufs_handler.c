vrrp_netlink_monitor_rcv_bufs_handler(vector_t *strvec)
{
	unsigned val;

	if (!strvec)
		return;

	val = get_netlink_rcv_bufs_size(strvec, "vrrp_netlink_monitor");

	if (val)
		global_data->vrrp_netlink_monitor_rcv_bufs = val;
}
