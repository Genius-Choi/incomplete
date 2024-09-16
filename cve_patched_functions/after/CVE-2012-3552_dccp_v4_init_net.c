static int __net_init dccp_v4_init_net(struct net *net)
{
	if (dccp_hashinfo.bhash == NULL)
		return -ESOCKTNOSUPPORT;

	return inet_ctl_sock_create(&net->dccp.v4_ctl_sk, PF_INET,
				    SOCK_DCCP, IPPROTO_DCCP, net);
}
