fm_pm_status_query
(
	IN		p_fm_config_conx_hdlt		hdl,
	IN		fm_mgr_action_t				action,
		OUT	fm_pm_status_t				*info,
		OUT	fm_msg_ret_code_t			*ret_code
)
{
	p_hsm_com_client_hdl_t	client_hdl;

    if ( (client_hdl = get_mgr_hdl(hdl,FM_MGR_PM)) != NULL )
    {
        return fm_mgr_general_query(client_hdl,action,FM_DT_PM_STATUS,sizeof(*info),info,ret_code);
    }

	return FM_CONF_ERROR;
}
