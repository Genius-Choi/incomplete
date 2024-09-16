static int inet_dump_ifaddr(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	int h, s_h;
	int idx, s_idx;
	int ip_idx, s_ip_idx;
	struct net_device *dev;
	struct in_device *in_dev;
	struct in_ifaddr *ifa;
	struct hlist_head *head;

	s_h = cb->args[0];
	s_idx = idx = cb->args[1];
	s_ip_idx = ip_idx = cb->args[2];

	for (h = s_h; h < NETDEV_HASHENTRIES; h++, s_idx = 0) {
		idx = 0;
		head = &net->dev_index_head[h];
		rcu_read_lock();
		cb->seq = atomic_read(&net->ipv4.dev_addr_genid) ^
			  net->dev_base_seq;
		hlist_for_each_entry_rcu(dev, head, index_hlist) {
			if (idx < s_idx)
				goto cont;
			if (h > s_h || idx > s_idx)
				s_ip_idx = 0;
			in_dev = __in_dev_get_rcu(dev);
			if (!in_dev)
				goto cont;

			for (ifa = in_dev->ifa_list, ip_idx = 0; ifa;
			     ifa = ifa->ifa_next, ip_idx++) {
				if (ip_idx < s_ip_idx)
					continue;
				if (inet_fill_ifaddr(skb, ifa,
					     NETLINK_CB(cb->skb).portid,
					     cb->nlh->nlmsg_seq,
					     RTM_NEWADDR, NLM_F_MULTI) < 0) {
					rcu_read_unlock();
					goto done;
				}
				nl_dump_check_consistent(cb, nlmsg_hdr(skb));
			}
cont:
			idx++;
		}
		rcu_read_unlock();
	}

done:
	cb->args[0] = h;
	cb->args[1] = idx;
	cb->args[2] = ip_idx;

	return skb->len;
}
