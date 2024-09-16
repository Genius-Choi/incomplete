static BOOL freerdp_peer_get_fds(freerdp_peer* client, void** rfds, int* rcount)
{
	rfds[*rcount] = (void*)(long)(client->context->rdp->transport->TcpIn->sockfd);
	(*rcount)++;

	return TRUE;
}
