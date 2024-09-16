static void __net_exit dccp_v6_exit_net(struct net *net)
{
	inet_ctl_sock_destroy(net->dccp.v6_ctl_sk);
}
