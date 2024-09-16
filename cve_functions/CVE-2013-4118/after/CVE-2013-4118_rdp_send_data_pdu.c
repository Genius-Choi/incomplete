BOOL rdp_send_data_pdu(rdpRdp* rdp, STREAM* s, BYTE type, UINT16 channel_id)
{
	UINT16 length;
	UINT32 sec_bytes;
	BYTE* sec_hold;

	length = stream_get_length(s);
	stream_set_pos(s, 0);

	rdp_write_header(rdp, s, length, MCS_GLOBAL_CHANNEL_ID);

	sec_bytes = rdp_get_sec_bytes(rdp);
	sec_hold = s->p;
	stream_seek(s, sec_bytes);

	rdp_write_share_control_header(s, length - sec_bytes, PDU_TYPE_DATA, channel_id);
	rdp_write_share_data_header(s, length - sec_bytes, type, rdp->settings->ShareId);

	s->p = sec_hold;
	length += rdp_security_stream_out(rdp, s, length);

	stream_set_pos(s, length);
	if (transport_write(rdp->transport, s) < 0)
		return FALSE;

	return TRUE;
}
