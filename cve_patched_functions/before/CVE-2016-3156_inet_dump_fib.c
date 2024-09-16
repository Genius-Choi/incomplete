static int inet_dump_fib(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	unsigned int h, s_h;
	unsigned int e = 0, s_e;
	struct fib_table *tb;
	struct hlist_head *head;
	int dumped = 0;

	if (nlmsg_len(cb->nlh) >= sizeof(struct rtmsg) &&
	    ((struct rtmsg *) nlmsg_data(cb->nlh))->rtm_flags & RTM_F_CLONED)
		return skb->len;

	s_h = cb->args[0];
	s_e = cb->args[1];

	rcu_read_lock();

	for (h = s_h; h < FIB_TABLE_HASHSZ; h++, s_e = 0) {
		e = 0;
		head = &net->ipv4.fib_table_hash[h];
		hlist_for_each_entry_rcu(tb, head, tb_hlist) {
			if (e < s_e)
				goto next;
			if (dumped)
				memset(&cb->args[2], 0, sizeof(cb->args) -
						 2 * sizeof(cb->args[0]));
			if (fib_table_dump(tb, skb, cb) < 0)
				goto out;
			dumped = 1;
next:
			e++;
		}
	}
out:
	rcu_read_unlock();

	cb->args[1] = e;
	cb->args[0] = h;

	return skb->len;
}
