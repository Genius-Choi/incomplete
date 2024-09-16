int sm_looptest_show_switch_lfts(p_fm_config_conx_hdlt hdl, fm_mgr_type_t mgr, int argc, char *argv[]) {
	fm_mgr_config_errno_t		res;
	fm_msg_ret_code_t			ret_code;
	uint8_t 					data[BUF_SZ];
	int							index=-1;
	fm_config_interation_data_t	interationData;
	int							start;

	if (argc > 1) {
		printf("Error: only 1 argument expected\n");
		return 0;
	}
	if (argc == 1) {
		index = atol(argv[0]);
	}
	memset(&interationData, 0, sizeof(fm_config_interation_data_t));
	interationData.start = start = 1;
	interationData.index = index;
	while (!interationData.done) {
		memcpy(data, &interationData, sizeof(fm_config_interation_data_t));
		if((res = fm_mgr_simple_query(hdl, FM_ACT_GET, FM_DT_SM_LOOP_TEST_SHOW_LFTS, mgr,
						BUF_SZ, data, &ret_code)) != FM_CONF_OK) {
			fprintf(stderr, "sm_looptest_show_switch_lfts: Failed to retrieve data: \n"
		   		"\tError:(%d) %s \n\tRet code:(%d) %s\n",
		   		res, fm_mgr_get_error_str(res),ret_code,
		   	fm_mgr_get_resp_error_str(ret_code));
			return 0;
		}
		if (start) {
			start = 0;
			if (index == -1)
				printf("Successfully sent Loop Test LFT show for node index (all) to local SM instance\n");
			else
				printf("Successfully sent Loop Test LFT show for node index %d to local SM instance\n", index);
		}
		memcpy(&interationData, data, sizeof(fm_config_interation_data_t));
		printf("%s", interationData.intermediateBuffer);
	}
	return 0;
}
