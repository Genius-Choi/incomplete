running_checker(void)
{
	return (__test_bit(DAEMON_CHECKERS, &daemon_mode) &&
	    (global_data->have_checker_config ||
	     __test_bit(RUN_ALL_CHILDREN, &daemon_mode)));
}
