int sm_state_dump(p_fm_config_conx_hdlt hdl, fm_mgr_type_t mgr, int argc, char *argv[]) {
	fm_mgr_config_errno_t	res;
	fm_msg_ret_code_t		ret_code;
    char dirName[256];

	if (argc == 1 && strlen(argv[0]) < 256) {
		strncpy(dirName, argv[0], sizeof(dirName));
		dirName[sizeof(dirName)-1]=0;
	} else {
		sprintf(dirName, "/tmp");
	}

	printf("Sending command to dump the SM state into the directory %s\n", dirName);

	if((res = fm_mgr_simple_query(hdl, FM_ACT_GET, FM_DT_SM_DUMP_STATE, mgr, 
								  strlen(dirName) + 1, dirName, &ret_code)) != FM_CONF_OK)
	{
		fprintf(stderr, "sm_state_dump: Failed to retrieve data: \n"
			   "\tError:(%d) %s \n\tRet code:(%d) %s\n",
			   res, fm_mgr_get_error_str(res),ret_code,
			   fm_mgr_get_resp_error_str(ret_code));
	} else {
		printf("Successfully sent state dump command to local SM instance\n");
	}

	return 0;
}
