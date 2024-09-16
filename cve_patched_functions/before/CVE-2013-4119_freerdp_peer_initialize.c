static BOOL freerdp_peer_initialize(freerdp_peer* client)
{
	client->context->rdp->settings->ServerMode = TRUE;
	client->context->rdp->settings->FrameAcknowledge = 0;
	client->context->rdp->settings->LocalConnection = client->local;
	client->context->rdp->state = CONNECTION_STATE_INITIAL;

	if (client->context->rdp->settings->RdpKeyFile != NULL)
	{
		client->context->rdp->settings->RdpServerRsaKey =
		    key_new(client->context->rdp->settings->RdpKeyFile);
	}

	return TRUE;
}
