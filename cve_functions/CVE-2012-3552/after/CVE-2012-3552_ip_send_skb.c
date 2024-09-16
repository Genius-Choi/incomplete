int ip_send_skb(struct sk_buff *skb)
{
	struct net *net = sock_net(skb->sk);
	int err;

	err = ip_local_out(skb);
	if (err) {
		if (err > 0)
			err = net_xmit_errno(err);
		if (err)
			IP_INC_STATS(net, IPSTATS_MIB_OUTDISCARDS);
	}

	return err;
}
