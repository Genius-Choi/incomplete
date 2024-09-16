BOOL transport_disconnect(rdpTransport* transport)
{
	BOOL status = TRUE;

	if (transport->layer == TRANSPORT_LAYER_TLS)
		status &= tls_disconnect(transport->TlsIn);

	if (transport->layer == TRANSPORT_LAYER_TSG)
	{
		tsg_disconnect(transport->tsg);
	}
	else
	{
		status &= tcp_disconnect(transport->TcpIn);
	}

	return status;
}
