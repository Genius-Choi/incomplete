fm_mgr_config_clear_error_map
(
	IN		p_fm_config_conx_hdlt	hdl
)
{
	if(hdl->error_map.err_set)
		memset(&hdl->error_map,0,sizeof(hdl->error_map));

	return FM_CONF_OK;
}
