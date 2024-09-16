fm_mgr_simple_query
(
	IN      p_fm_config_conx_hdlt       hdl,
	IN      fm_mgr_action_t             action,
	IN      fm_datatype_t               data_type_id,
	IN		fm_mgr_type_t				mgr,
	IN      int                         data_len,
		OUT void                        *data,
		OUT fm_msg_ret_code_t           *ret_code
)
{
	p_hsm_com_client_hdl_t client_hdl;

	if ( (client_hdl = get_mgr_hdl(hdl,mgr)) != NULL ) {
		return fm_mgr_general_query(client_hdl,action,data_type_id,data_len,data,ret_code);
	}
	return FM_CONF_ERROR;
}
