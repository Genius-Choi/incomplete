BOOL transport_connect_tls(rdpTransport* transport)
{
	if (transport->layer == TRANSPORT_LAYER_TSG)
		return TRUE;

	if (transport->TlsIn == NULL)
		transport->TlsIn = tls_new(transport->settings);

	if (transport->TlsOut == NULL)
		transport->TlsOut = transport->TlsIn;

	transport->layer = TRANSPORT_LAYER_TLS;
	transport->TlsIn->sockfd = transport->TcpIn->sockfd;

	if (tls_connect(transport->TlsIn) != TRUE)
	{
		if (!connectErrorCode)
			connectErrorCode = TLSCONNECTERROR;

		tls_free(transport->TlsIn);

		if (transport->TlsIn == transport->TlsOut)
			transport->TlsIn = transport->TlsOut = NULL;
		else
			transport->TlsIn = NULL;

		return FALSE;
	}

	return TRUE;
}
