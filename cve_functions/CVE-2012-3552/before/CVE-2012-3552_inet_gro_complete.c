static int inet_gro_complete(struct sk_buff *skb)
{
	const struct net_protocol *ops;
	struct iphdr *iph = ip_hdr(skb);
	int proto = iph->protocol & (MAX_INET_PROTOS - 1);
	int err = -ENOSYS;
	__be16 newlen = htons(skb->len - skb_network_offset(skb));

	csum_replace2(&iph->check, iph->tot_len, newlen);
	iph->tot_len = newlen;

	rcu_read_lock();
	ops = rcu_dereference(inet_protos[proto]);
	if (WARN_ON(!ops || !ops->gro_complete))
		goto out_unlock;

	err = ops->gro_complete(skb);

out_unlock:
	rcu_read_unlock();

	return err;
}
