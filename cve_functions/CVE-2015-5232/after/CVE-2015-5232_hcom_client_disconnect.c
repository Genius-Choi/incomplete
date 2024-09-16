hcom_client_disconnect
(
	IN p_hsm_com_client_hdl_t p_hdl		
)
{
	return unix_client_disconnect(p_hdl);
}
