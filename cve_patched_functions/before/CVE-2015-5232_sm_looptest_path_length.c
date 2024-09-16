int sm_looptest_path_length(p_fm_config_conx_hdlt hdl, fm_mgr_type_t mgr, int argc, char *argv[]) {
	fm_mgr_config_errno_t	res;
	fm_msg_ret_code_t		ret_code;
	int						plen=3;
	uint8_t                 data[BUF_SZ];

	if (argc > 1) {
		printf("Error: only 1 argument expected\n");
		return 0;
	}

	if (argc == 1) {
		plen = atol(argv[0]);
		if (plen < 2 || plen > 4) {
			printf("Error: length must be 2-4\n");
			return 0;
		}
	}
	*(int*)data = plen;
	if((res = fm_mgr_simple_query(hdl, FM_ACT_GET, FM_DT_SM_LOOP_TEST_PATH_LEN, mgr, 
								  BUF_SZ, data, &ret_code)) != FM_CONF_OK)
	{
		fprintf(stderr, "sm_looptest_path_length: Failed to retrieve data: \n"
			   "\tError:(%d) %s \n\tRet code:(%d) %s\n",
			   res, fm_mgr_get_error_str(res),ret_code,
			   fm_mgr_get_resp_error_str(ret_code));
	} else {
		printf("Successfully sent Loop Test Path Length set to %d control to local SM instance\n", plen);
		data[BUF_SZ-1]=0;
		printf("%s", (char*) data);
	}
	return 0;
}
