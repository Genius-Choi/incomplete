static void netlink_remove(struct sock *sk)
{
	netlink_table_grab();
	if (sk_del_node_init(sk))
		nl_table[sk->sk_protocol].hash.entries--;
	if (nlk_sk(sk)->subscriptions)
		__sk_del_bind_node(sk);
	netlink_table_ungrab();
}
