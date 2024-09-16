BOOL transport_connect(rdpTransport* transport, const char* hostname, UINT16 port)
{
	BOOL status = FALSE;
	rdpSettings* settings = transport->settings;

	transport->async = transport->settings->AsyncTransport;

	if (transport->async)
	{
		transport->stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		transport->thread = CreateThread(NULL, 0,
				(LPTHREAD_START_ROUTINE) transport_client_thread, transport, 0, NULL);
	}

	if (transport->settings->GatewayUsageMethod)
	{
		transport->layer = TRANSPORT_LAYER_TSG;
		transport->TcpOut = tcp_new(settings);

		status = tcp_connect(transport->TcpIn, settings->GatewayHostname, 443);

		if (status)
			status = tcp_connect(transport->TcpOut, settings->GatewayHostname, 443);

		if (status)
			status = transport_tsg_connect(transport, hostname, port);
	}
	else
	{
		status = tcp_connect(transport->TcpIn, hostname, port);

		transport->SplitInputOutput = FALSE;
		transport->TcpOut = transport->TcpIn;
	}

	return status;
}
