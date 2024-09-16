void __init tcp_v4_init(void)
{
	inet_hashinfo_init(&tcp_hashinfo);
	if (register_pernet_subsys(&tcp_sk_ops))
		panic("Failed to create the TCP control socket.\n");
}
