fm_mgr_config_get_error_map_entry
(
	IN		p_fm_config_conx_hdlt	hdl,
	IN		uint64_t				mask,
		OUT	fm_mgr_config_errno_t	*error_code
)
{
	int i;

	for(i=0;i<64;i++){
		if(mask & 0x01){
			if((mask >> 1)){
				return FM_CONF_ERROR;
			}
			*error_code = hdl->error_map.map[i];
			return FM_CONF_OK;
		}
		mask >>= 1;
	}

	return FM_CONF_ERROR;
}
