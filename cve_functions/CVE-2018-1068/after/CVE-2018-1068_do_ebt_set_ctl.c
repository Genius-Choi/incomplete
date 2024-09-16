static int do_ebt_set_ctl(struct sock *sk,
	int cmd, void __user *user, unsigned int len)
{
	int ret;
	struct net *net = sock_net(sk);

	if (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		return -EPERM;

	switch (cmd) {
	case EBT_SO_SET_ENTRIES:
		ret = do_replace(net, user, len);
		break;
	case EBT_SO_SET_COUNTERS:
		ret = update_counters(net, user, len);
		break;
	default:
		ret = -EINVAL;
	}
	return ret;
}
