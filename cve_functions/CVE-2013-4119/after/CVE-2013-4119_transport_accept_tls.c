BOOL transport_accept_tls(rdpTransport* transport)
{
	if (transport->TlsIn == NULL)
		transport->TlsIn = tls_new(transport->settings);

	if (transport->TlsOut == NULL)
		transport->TlsOut = transport->TlsIn;

	transport->layer = TRANSPORT_LAYER_TLS;
	transport->TlsIn->sockfd = transport->TcpIn->sockfd;

	if (tls_accept(transport->TlsIn, transport->settings->CertificateFile, transport->settings->PrivateKeyFile) != TRUE)
		return FALSE;

	return TRUE;
}
