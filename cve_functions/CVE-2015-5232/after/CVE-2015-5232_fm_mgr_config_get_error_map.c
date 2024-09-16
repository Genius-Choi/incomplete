fm_mgr_config_get_error_map
(
	IN		p_fm_config_conx_hdlt	hdl,
		OUT	fm_error_map_t			*error_map
)
{
	if(error_map){
		memcpy(error_map,&hdl->error_map,sizeof(fm_error_map_t));
		return FM_CONF_OK;
	}

	return FM_CONF_ERROR;
}
