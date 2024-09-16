hcom_client_connect
(
	IN p_hsm_com_client_hdl_t p_hdl		
)
{
	return unix_client_connect(p_hdl);
}
