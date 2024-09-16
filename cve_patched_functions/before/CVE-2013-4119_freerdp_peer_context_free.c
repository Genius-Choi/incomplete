void freerdp_peer_context_free(freerdp_peer* client)
{
	IFCALL(client->ContextFree, client, client->context);
}
