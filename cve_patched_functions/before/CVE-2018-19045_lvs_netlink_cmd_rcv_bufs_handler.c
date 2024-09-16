lvs_netlink_cmd_rcv_bufs_handler(vector_t *strvec)
{
	unsigned val;

	if (!strvec)
		return;

	val = get_netlink_rcv_bufs_size(strvec, "lvs_netlink_cmd");

	if (val)
		global_data->lvs_netlink_cmd_rcv_bufs = val;
}
