config_test_exit(void)
{
	config_err_t config_err = get_config_status();

	switch (config_err) {
	case CONFIG_OK:
		exit(KEEPALIVED_EXIT_OK);
	case CONFIG_FILE_NOT_FOUND:
	case CONFIG_BAD_IF:
	case CONFIG_FATAL:
		exit(KEEPALIVED_EXIT_CONFIG);
	case CONFIG_SECURITY_ERROR:
		exit(KEEPALIVED_EXIT_CONFIG_TEST_SECURITY);
	default:
		exit(KEEPALIVED_EXIT_CONFIG_TEST);
	}
}
