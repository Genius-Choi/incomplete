void rdp_set_blocking_mode(rdpRdp* rdp, BOOL blocking)
{
	rdp->transport->ReceiveCallback = rdp_recv_callback;
	rdp->transport->ReceiveExtra = rdp;
	transport_set_blocking_mode(rdp->transport, blocking);
}
