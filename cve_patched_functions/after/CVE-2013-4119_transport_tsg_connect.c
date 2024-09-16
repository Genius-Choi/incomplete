BOOL transport_tsg_connect(rdpTransport* transport, const char* hostname, UINT16 port)
{
	rdpTsg* tsg = tsg_new(transport);

	tsg->transport = transport;
	transport->tsg = tsg;
	transport->SplitInputOutput = TRUE;

	if (transport->TlsIn == NULL)
		transport->TlsIn = tls_new(transport->settings);

	transport->TlsIn->sockfd = transport->TcpIn->sockfd;

	if (transport->TlsOut == NULL)
		transport->TlsOut = tls_new(transport->settings);

	transport->TlsOut->sockfd = transport->TcpOut->sockfd;

	if (tls_connect(transport->TlsIn) != TRUE)
		return FALSE;

	if (tls_connect(transport->TlsOut) != TRUE)
		return FALSE;

	if (!tsg_connect(tsg, hostname, port))
		return FALSE;

	return TRUE;
}
