static void ndp_sock_close(struct ndp *ndp)
{
	close(ndp->sock);
}
