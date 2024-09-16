fm_mgr_get_error_str
(
	IN		fm_mgr_config_errno_t err
)
{
	switch(err){
		case FM_CONF_ERR_LEN:
			return "Response data legth invalid";
		case FM_CONF_ERR_VERSION:
			return "Client/Server version mismatch";
		case FM_CONF_ERR_DISC:
			return "Not connected";
		case FM_CONF_TEST:
			return "Test message";
		case FM_CONF_OK:
			return "Ok";
		case FM_CONF_ERROR:
			return "General error";
		case FM_CONF_NO_RESOURCES:
			return "Out of resources";
		case FM_CONF_NO_MEM:
			return "No memory";
		case FM_CONF_PATH_ERR:
			return "Invalid path";
		case FM_CONF_BAD:
			return "Bad argument";
		case FM_CONF_BIND_ERR:
			return "Could not bind socket";
		case FM_CONF_SOCK_ERR:
			return "Could not create socket";
		case FM_CONF_CHMOD_ERR:
			return "Invalid permissions on socket";
		case FM_CONF_CONX_ERR:
			return "Connection Error";
		case FM_CONF_SEND_ERR:
			return "Send error";
		case FM_CONF_INIT_ERR:
			return "Could not initalize resource";
		case FM_CONF_NO_RESP:
			return "No Response";
		case FM_CONF_MAX_ERROR_NUM:
		default:
			return "Unknown error";
	}

	return "Unknown error";

}
