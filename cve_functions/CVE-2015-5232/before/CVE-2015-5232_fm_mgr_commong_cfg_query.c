fm_mgr_commong_cfg_query
(
	IN      p_fm_config_conx_hdlt       hdl,
	IN      fm_mgr_type_t               mgr,
	IN      fm_mgr_action_t             action,
		OUT fm_config_common_t          *info,
		OUT fm_msg_ret_code_t           *ret_code
)
{
	p_hsm_com_client_hdl_t client_hdl;

    if ( (client_hdl = get_mgr_hdl(hdl,mgr)) != NULL )
    {
        return fm_mgr_general_query(client_hdl,action,FM_DT_COMMON,sizeof(fm_config_common_t),info,ret_code);
    }

	return FM_CONF_ERROR;

}
