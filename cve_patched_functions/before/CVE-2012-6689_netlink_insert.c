static int netlink_insert(struct sock *sk, struct net *net, u32 pid)
{
	struct nl_pid_hash *hash = &nl_table[sk->sk_protocol].hash;
	struct hlist_head *head;
	int err = -EADDRINUSE;
	struct sock *osk;
	struct hlist_node *node;
	int len;

	netlink_table_grab();
	head = nl_pid_hashfn(hash, pid);
	len = 0;
	sk_for_each(osk, node, head) {
		if (net_eq(sock_net(osk), net) && (nlk_sk(osk)->pid == pid))
			break;
		len++;
	}
	if (node)
		goto err;

	err = -EBUSY;
	if (nlk_sk(sk)->pid)
		goto err;

	err = -ENOMEM;
	if (BITS_PER_LONG > 32 && unlikely(hash->entries >= UINT_MAX))
		goto err;

	if (len && nl_pid_hash_dilute(hash, len))
		head = nl_pid_hashfn(hash, pid);
	hash->entries++;
	nlk_sk(sk)->pid = pid;
	sk_add_node(sk, head);
	err = 0;

err:
	netlink_table_ungrab();
	return err;
}
