int sm_resume_sweeps(p_fm_config_conx_hdlt hdl, fm_mgr_type_t mgr, int argc, char *argv[]) {

	fm_mgr_config_errno_t	res;
	fm_msg_ret_code_t		ret_code;

	if((res = fm_mgr_simple_query(hdl, FM_ACT_GET, FM_DT_RESUME_SWEEPS, mgr, 0, NULL, &ret_code)) != FM_CONF_OK) {
		fprintf(stderr, "sm_pause_sweeps: Failed to retrieve data: \n"
		       "\tError:(%d) %s \n\tRet code:(%d) %s\n",
		       res, fm_mgr_get_error_str(res),ret_code,
		       fm_mgr_get_resp_error_str(ret_code));
	} else {
		printf("sm_resume_sweeps: Successfully sent Resume SM Sweeps command to local mgr instance\n");
    }

	return 0;
}
