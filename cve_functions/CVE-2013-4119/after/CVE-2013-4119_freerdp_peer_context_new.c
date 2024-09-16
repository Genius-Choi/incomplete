void freerdp_peer_context_new(freerdp_peer* client)
{
	rdpRdp* rdp;

	rdp = rdp_new(NULL);
	client->input = rdp->input;
	client->update = rdp->update;
	client->settings = rdp->settings;

	client->context = (rdpContext*) malloc(client->ContextSize);
	ZeroMemory(client->context, client->ContextSize);

	client->context->rdp = rdp;
	client->context->peer = client;
	client->context->input = client->input;
	client->context->update = client->update;
	client->context->settings = client->settings;

	client->update->context = client->context;
	client->input->context = client->context;

	update_register_server_callbacks(client->update);

	transport_attach(rdp->transport, client->sockfd);

	rdp->transport->ReceiveCallback = peer_recv_callback;
	rdp->transport->ReceiveExtra = client;
	transport_set_blocking_mode(rdp->transport, FALSE);

	IFCALL(client->ContextNew, client, client->context);
}
