fm_mgr_general_query
(
	IN      p_hsm_com_client_hdl_t      client_hdl,
	IN      fm_mgr_action_t             action,
	IN      fm_datatype_t               data_type_id,
	IN      int                         data_len,
		OUT void                        *data,
		OUT fm_msg_ret_code_t           *ret_code
)
{
	fm_config_datagram_t    *dg;
	hsm_com_datagram_t      com_dg;
	int                     len;
	hsm_com_errno_t			com_res;

	len = data_len + (sizeof(fm_config_datagram_header_t));


	if ( (dg = malloc(len)) == NULL )
	{
		return FM_CONF_NO_MEM;
	}

	dg->header.action = action;
	dg->header.data_id = data_type_id;
	dg->header.data_len = data_len;

	memcpy(&dg->data[0],data,data_len);

	com_dg.buf = (char*)dg;
	com_dg.buf_size = len;
	com_dg.data_len = len;

	if ( (com_res = hcom_client_send_data(client_hdl,60,&com_dg,&com_dg)) != HSM_COM_OK )
	{
		free(dg);
		if(com_res == HSM_COM_NOT_CONNECTED)
		{
			return FM_CONF_ERR_DISC; 
		}
		return FM_CONF_NO_RESP;
	}

	if ( ret_code )
		*ret_code = dg->header.ret_code;

	if ( dg->header.ret_code != FM_RET_OK )
	{
		free(dg);
		return FM_CONF_ERROR;
	} else
	{
		if ( dg->header.data_len != data_len )
		{
			free(dg);
			if ( ret_code )
				*ret_code = FM_RET_BAD_RET_LEN;
			return FM_CONF_ERR_LEN;
		}
		memcpy(data,&dg->data[0],data_len);
	}

	free(dg);
	return FM_CONF_OK;
}
