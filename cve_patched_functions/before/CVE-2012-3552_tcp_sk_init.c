static int __net_init tcp_sk_init(struct net *net)
{
	return inet_ctl_sock_create(&net->ipv4.tcp_sock,
				    PF_INET, SOCK_RAW, IPPROTO_TCP, net);
}
