freerdp_peer* freerdp_peer_new(int sockfd)
{
	freerdp_peer* client;

	client = (freerdp_peer*) malloc(sizeof(freerdp_peer));
	ZeroMemory(client, sizeof(freerdp_peer));

	freerdp_tcp_set_no_delay(sockfd, TRUE);

	if (client != NULL)
	{
		client->sockfd = sockfd;
		client->ContextSize = sizeof(rdpContext);
		client->Initialize = freerdp_peer_initialize;
		client->GetFileDescriptor = freerdp_peer_get_fds;
		client->CheckFileDescriptor = freerdp_peer_check_fds;
		client->Close = freerdp_peer_close;
		client->Disconnect = freerdp_peer_disconnect;
		client->SendChannelData = freerdp_peer_send_channel_data;
	}

	return client;
}
