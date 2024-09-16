STREAM* rdp_send_stream_init(rdpRdp* rdp)
{
	STREAM* s;

	s = transport_send_stream_init(rdp->transport, 2048);
	stream_seek(s, RDP_PACKET_HEADER_MAX_LENGTH);
	rdp_security_stream_init(rdp, s);

	return s;
}
