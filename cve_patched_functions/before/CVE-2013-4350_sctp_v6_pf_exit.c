void sctp_v6_pf_exit(void)
{
	list_del(&sctp_af_inet6.list);
}
