int ndp_call_eventfd_handler(struct ndp *ndp)
{
	return ndp_sock_recv(ndp);
}
