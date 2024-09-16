STREAM* rdp_pdu_init(rdpRdp* rdp)
{
	STREAM* s;
	s = transport_send_stream_init(rdp->transport, 2048);
	stream_seek(s, RDP_PACKET_HEADER_MAX_LENGTH);
	rdp_security_stream_init(rdp, s);
	stream_seek(s, RDP_SHARE_CONTROL_HEADER_LENGTH);
	return s;
}
