GetStatusInfo(struct upnphttp * h, const char * action, const char * ns)
{
	static const char resp[] =
		"<u:%sResponse "
		"xmlns:u=\"%s\">"
		"<NewConnectionStatus>%s</NewConnectionStatus>"
		"<NewLastConnectionError>ERROR_NONE</NewLastConnectionError>"
		"<NewUptime>%ld</NewUptime>"
		"</u:%sResponse>";

	char body[512];
	int bodylen;
	time_t uptime;
	const char * status;
	/* ConnectionStatus possible values :
	 * Unconfigured, Connecting, Connected, PendingDisconnect,
	 * Disconnecting, Disconnected */

	status = get_wan_connection_status_str(ext_if_name);
	uptime = upnp_get_uptime();
	bodylen = snprintf(body, sizeof(body), resp,
		action, ns, /*SERVICE_TYPE_WANIPC,*/
		status, (long)uptime, action);
	BuildSendAndCloseSoapResp(h, body, bodylen);
}
