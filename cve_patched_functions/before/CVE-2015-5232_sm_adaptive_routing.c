int sm_adaptive_routing(p_fm_config_conx_hdlt hdl, fm_mgr_type_t mgr, int argc, char *argv[]) {
	fm_mgr_config_errno_t	res;
	fm_msg_ret_code_t		ret_code;
	uint32_t				enable=0;

	if (argc == 1) {
		enable = atol(argv[0]);
		if((res = fm_mgr_simple_query(hdl, FM_ACT_GET, FM_DT_SM_SET_ADAPTIVE_ROUTING, mgr, sizeof(enable), (void*)&enable, &ret_code)) != FM_CONF_OK)
		{
			fprintf(stderr, "sm_adaptive_routing: Failed to retrieve data: \n"
		       	"\tError:(%d) %s \n\tRet code:(%d) %s\n",
		       	res, fm_mgr_get_error_str(res),ret_code,
		       	fm_mgr_get_resp_error_str(ret_code));
		} else {
			printf("Successfully sent SM Adaptive Routing control to local SM instance\n");
    	}

	} else if (argc == 0) {
		if((res = fm_mgr_simple_query(hdl, FM_ACT_GET, FM_DT_SM_GET_ADAPTIVE_ROUTING, mgr, sizeof(enable), (void*)&enable, &ret_code)) != FM_CONF_OK)
		{
			fprintf(stderr, "sm_adaptive_routing: Failed to retrieve data: \n"
		       	"\tError:(%d) %s \n\tRet code:(%d) %s\n",
		       	res, fm_mgr_get_error_str(res),ret_code,
		       	fm_mgr_get_resp_error_str(ret_code));
		} else {
			printf("SM Adaptive Routing is %s\n", enable ? "enabled" : "disabled");
		}
	}
	return 0;
}
