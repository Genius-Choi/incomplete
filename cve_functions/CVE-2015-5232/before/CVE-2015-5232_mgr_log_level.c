int mgr_log_level(p_fm_config_conx_hdlt hdl, fm_mgr_type_t mgr, int argc, char *argv[]) {
	fm_mgr_config_errno_t	res;
	fm_msg_ret_code_t		ret_code;
	uint32_t 				loglevel=0;

	if (mgr == FM_MGR_PM) {
		fprintf(stderr, "pmLogLevel:\n");
		fprintf(stderr, "\tThis command is not supported any more.  The logging of the\n");
		fprintf(stderr, "\tPerformance Manager(PM) is now\n");
		fprintf(stderr, "\tbased on the logging of the Subnet manager(SM).  Use the\n");
		fprintf(stderr, "\tsmLogLevel command for changing the logging level of the\n");
		fprintf(stderr, "\tSM and PM\n");
	} else if (argc == 1) {
		loglevel = atol(argv[0]);
		if((res = fm_mgr_simple_query(hdl, FM_ACT_GET, FM_DT_LOG_LEVEL, mgr, sizeof(loglevel), (void *)&loglevel, &ret_code)) != FM_CONF_OK)
		{
			fprintf(stderr, "mgr_log_level: Failed to retrieve data: \n"
				   "\tError:(%d) %s \n\tRet code:(%d) %s\n",
				   res, fm_mgr_get_error_str(res),ret_code,
				   fm_mgr_get_resp_error_str(ret_code));
		} else {
			printf("mgr_log_level: Successfully sent Log Level control to local mgr instance\n");
		}
	} else {
		fprintf(stderr, "mgr_log_level: must specify the log level parameter (1 > 5): \n");
	}

	return 0;
}
