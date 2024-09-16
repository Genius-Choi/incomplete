int sm_looptest_show_config(p_fm_config_conx_hdlt hdl, fm_mgr_type_t mgr, int argc, char *argv[]) {
	fm_mgr_config_errno_t	res;
	fm_msg_ret_code_t		ret_code;
	uint8_t data[BUF_SZ];

	if((res = fm_mgr_simple_query(hdl, FM_ACT_GET, FM_DT_SM_LOOP_TEST_SHOW_CONFIG, mgr, BUF_SZ, data, &ret_code)) != FM_CONF_OK)
	{
		fprintf(stderr, "sm_looptest_show_config: Failed to retrieve data: \n"
		       "\tError:(%d) %s \n\tRet code:(%d) %s\n",
		       res, fm_mgr_get_error_str(res),ret_code,
		       fm_mgr_get_resp_error_str(ret_code));
	} else {
		printf("Successfully sent Loop Test configuration show to local SM instance\n");
		data[BUF_SZ-1]=0;
		printf("%s", (char*) data);
    }
	return 0;
}
