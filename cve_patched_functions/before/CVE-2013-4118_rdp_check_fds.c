int rdp_check_fds(rdpRdp* rdp)
{
	return transport_check_fds(&(rdp->transport));
}
