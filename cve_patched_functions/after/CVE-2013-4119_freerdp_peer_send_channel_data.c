static int freerdp_peer_send_channel_data(freerdp_peer* client, int channelId, BYTE* data, int size)
{
	return rdp_send_channel_data(client->context->rdp, channelId, data, size);
}
