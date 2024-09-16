void ndp_close(struct ndp *ndp)
{
	ndp_sock_close(ndp);
	free(ndp);
}
