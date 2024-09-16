hcom_client_send_data
(
	IN		p_hsm_com_client_hdl_t	p_hdl,
	IN		int						timeout_s,
	IN		hsm_com_datagram_t		*data,
		OUT	hsm_com_datagram_t		*res
)
{
	if(p_hdl->client_state == HSM_COM_C_STATE_CT)
		return unix_sck_send_data(p_hdl, timeout_s, data, res); 

	return HSM_COM_NOT_CONNECTED;
}
