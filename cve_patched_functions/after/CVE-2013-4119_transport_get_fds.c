void transport_get_fds(rdpTransport* transport, void** rfds, int* rcount)
{
	void* pfd;

#ifdef _WIN32
	rfds[*rcount] = transport->TcpIn->wsa_event;
	(*rcount)++;

	if (transport->SplitInputOutput)
	{
		rfds[*rcount] = transport->TcpOut->wsa_event;
		(*rcount)++;
	}
#else
	rfds[*rcount] = (void*)(long)(transport->TcpIn->sockfd);
	(*rcount)++;

	if (transport->SplitInputOutput)
	{
		rfds[*rcount] = (void*)(long)(transport->TcpOut->sockfd);
		(*rcount)++;
	}
#endif

	pfd = GetEventWaitObject(transport->ReceiveEvent);

	if (pfd)
	{
		rfds[*rcount] = pfd;
		(*rcount)++;
	}

	if (transport->GatewayEvent)
	{
		pfd = GetEventWaitObject(transport->GatewayEvent);

		if (pfd)
		{
			rfds[*rcount] = pfd;
			(*rcount)++;
		}
	}
}
