int rdp_send_channel_data(rdpRdp* rdp, int channel_id, BYTE* data, int size)
{
	return freerdp_channel_send(rdp, channel_id, data, size);
}
