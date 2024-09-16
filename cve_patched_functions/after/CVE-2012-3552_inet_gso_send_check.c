static int inet_gso_send_check(struct sk_buff *skb)
{
	const struct iphdr *iph;
	const struct net_protocol *ops;
	int proto;
	int ihl;
	int err = -EINVAL;

	if (unlikely(!pskb_may_pull(skb, sizeof(*iph))))
		goto out;

	iph = ip_hdr(skb);
	ihl = iph->ihl * 4;
	if (ihl < sizeof(*iph))
		goto out;

	if (unlikely(!pskb_may_pull(skb, ihl)))
		goto out;

	__skb_pull(skb, ihl);
	skb_reset_transport_header(skb);
	iph = ip_hdr(skb);
	proto = iph->protocol & (MAX_INET_PROTOS - 1);
	err = -EPROTONOSUPPORT;

	rcu_read_lock();
	ops = rcu_dereference(inet_protos[proto]);
	if (likely(ops && ops->gso_send_check))
		err = ops->gso_send_check(skb);
	rcu_read_unlock();

out:
	return err;
}
