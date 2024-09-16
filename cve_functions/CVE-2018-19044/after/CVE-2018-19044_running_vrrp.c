running_vrrp(void)
{
	return (__test_bit(DAEMON_VRRP, &daemon_mode) &&
	    (global_data->have_vrrp_config ||
	     __test_bit(RUN_ALL_CHILDREN, &daemon_mode)));
}
