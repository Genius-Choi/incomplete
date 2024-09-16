void transport_free(rdpTransport* transport)
{
	if (transport != NULL)
	{
        SetEvent(transport->stopEvent);
        
		if (transport->ReceiveBuffer)
			Stream_Release(transport->ReceiveBuffer);

		StreamPool_Free(transport->ReceivePool);

		CloseHandle(transport->ReceiveEvent);
		CloseHandle(transport->connectedEvent);

		if (transport->TlsIn)
			tls_free(transport->TlsIn);

		if (transport->TlsOut != transport->TlsIn)
			tls_free(transport->TlsOut);

		tcp_free(transport->TcpIn);

		if (transport->TcpOut != transport->TcpIn)
			tcp_free(transport->TcpOut);

		tsg_free(transport->tsg);

		CloseHandle(transport->ReadMutex);
		CloseHandle(transport->WriteMutex);

		free(transport);
	}
}
