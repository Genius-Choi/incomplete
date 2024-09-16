int credssp_ntlm_server_init(rdpCredssp* credssp)
{
	freerdp* instance;
	rdpSettings* settings = credssp->settings;
	instance = (freerdp*) settings->instance;

	sspi_SecBufferAlloc(&credssp->PublicKey, credssp->transport->TlsIn->PublicKeyLength);
	CopyMemory(credssp->PublicKey.pvBuffer, credssp->transport->TlsIn->PublicKey, credssp->transport->TlsIn->PublicKeyLength);

	return 1;
}
