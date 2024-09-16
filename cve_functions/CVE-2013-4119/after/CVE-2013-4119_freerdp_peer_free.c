void freerdp_peer_free(freerdp_peer* client)
{
	if (client)
	{
		rdp_free(client->context->rdp);
		free(client->context);
		free(client);
	}
}
