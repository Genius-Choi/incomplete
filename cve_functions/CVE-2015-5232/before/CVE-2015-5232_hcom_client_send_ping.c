hcom_client_send_ping
(
	IN	p_hsm_com_client_hdl_t	p_hdl,	
	IN	int						timeout_s
)
{
	return unix_sck_send_ping(p_hdl,timeout_s);
}
