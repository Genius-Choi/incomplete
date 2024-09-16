void transport_get_read_handles(rdpTransport* transport, HANDLE* events, DWORD* count)
{
	events[*count] = tcp_get_event_handle(transport->TcpIn);
	(*count)++;

	if (transport->SplitInputOutput)
	{
		events[*count] = tcp_get_event_handle(transport->TcpOut);
		(*count)++;
	}

	if (transport->ReceiveEvent)
	{
		events[*count] = transport->ReceiveEvent;
		(*count)++;
	}

	if (transport->GatewayEvent)
	{
		events[*count] = transport->GatewayEvent;
		(*count)++;
	}
}
