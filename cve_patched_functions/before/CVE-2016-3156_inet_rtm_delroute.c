static int inet_rtm_delroute(struct sk_buff *skb, struct nlmsghdr *nlh)
{
	struct net *net = sock_net(skb->sk);
	struct fib_config cfg;
	struct fib_table *tb;
	int err;

	err = rtm_to_fib_config(net, skb, nlh, &cfg);
	if (err < 0)
		goto errout;

	tb = fib_get_table(net, cfg.fc_table);
	if (!tb) {
		err = -ESRCH;
		goto errout;
	}

	err = fib_table_delete(tb, &cfg);
errout:
	return err;
}
