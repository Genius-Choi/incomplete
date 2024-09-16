void rdp_recv(rdpRdp* rdp)
{
	STREAM* s;

	s = transport_recv_stream_init(rdp->transport, 4096);
	transport_read(rdp->transport, s);

	rdp_recv_pdu(rdp, s);
}
