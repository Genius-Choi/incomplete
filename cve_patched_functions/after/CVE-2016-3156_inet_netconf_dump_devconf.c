static int inet_netconf_dump_devconf(struct sk_buff *skb,
				     struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	int h, s_h;
	int idx, s_idx;
	struct net_device *dev;
	struct in_device *in_dev;
	struct hlist_head *head;

	s_h = cb->args[0];
	s_idx = idx = cb->args[1];

	for (h = s_h; h < NETDEV_HASHENTRIES; h++, s_idx = 0) {
		idx = 0;
		head = &net->dev_index_head[h];
		rcu_read_lock();
		cb->seq = atomic_read(&net->ipv4.dev_addr_genid) ^
			  net->dev_base_seq;
		hlist_for_each_entry_rcu(dev, head, index_hlist) {
			if (idx < s_idx)
				goto cont;
			in_dev = __in_dev_get_rcu(dev);
			if (!in_dev)
				goto cont;

			if (inet_netconf_fill_devconf(skb, dev->ifindex,
						      &in_dev->cnf,
						      NETLINK_CB(cb->skb).portid,
						      cb->nlh->nlmsg_seq,
						      RTM_NEWNETCONF,
						      NLM_F_MULTI,
						      NETCONFA_ALL) < 0) {
				rcu_read_unlock();
				goto done;
			}
			nl_dump_check_consistent(cb, nlmsg_hdr(skb));
cont:
			idx++;
		}
		rcu_read_unlock();
	}
	if (h == NETDEV_HASHENTRIES) {
		if (inet_netconf_fill_devconf(skb, NETCONFA_IFINDEX_ALL,
					      net->ipv4.devconf_all,
					      NETLINK_CB(cb->skb).portid,
					      cb->nlh->nlmsg_seq,
					      RTM_NEWNETCONF, NLM_F_MULTI,
					      NETCONFA_ALL) < 0)
			goto done;
		else
			h++;
	}
	if (h == NETDEV_HASHENTRIES + 1) {
		if (inet_netconf_fill_devconf(skb, NETCONFA_IFINDEX_DEFAULT,
					      net->ipv4.devconf_dflt,
					      NETLINK_CB(cb->skb).portid,
					      cb->nlh->nlmsg_seq,
					      RTM_NEWNETCONF, NLM_F_MULTI,
					      NETCONFA_ALL) < 0)
			goto done;
		else
			h++;
	}
done:
	cb->args[0] = h;
	cb->args[1] = idx;

	return skb->len;
}
