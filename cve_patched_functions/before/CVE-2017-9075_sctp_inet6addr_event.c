static int sctp_inet6addr_event(struct notifier_block *this, unsigned long ev,
				void *ptr)
{
	struct inet6_ifaddr *ifa = (struct inet6_ifaddr *)ptr;
	struct sctp_sockaddr_entry *addr = NULL;
	struct sctp_sockaddr_entry *temp;
	struct net *net = dev_net(ifa->idev->dev);
	int found = 0;

	switch (ev) {
	case NETDEV_UP:
		addr = kmalloc(sizeof(struct sctp_sockaddr_entry), GFP_ATOMIC);
		if (addr) {
			addr->a.v6.sin6_family = AF_INET6;
			addr->a.v6.sin6_port = 0;
			addr->a.v6.sin6_addr = ifa->addr;
			addr->a.v6.sin6_scope_id = ifa->idev->dev->ifindex;
			addr->valid = 1;
			spin_lock_bh(&net->sctp.local_addr_lock);
			list_add_tail_rcu(&addr->list, &net->sctp.local_addr_list);
			sctp_addr_wq_mgmt(net, addr, SCTP_ADDR_NEW);
			spin_unlock_bh(&net->sctp.local_addr_lock);
		}
		break;
	case NETDEV_DOWN:
		spin_lock_bh(&net->sctp.local_addr_lock);
		list_for_each_entry_safe(addr, temp,
					&net->sctp.local_addr_list, list) {
			if (addr->a.sa.sa_family == AF_INET6 &&
					ipv6_addr_equal(&addr->a.v6.sin6_addr,
						&ifa->addr)) {
				sctp_addr_wq_mgmt(net, addr, SCTP_ADDR_DEL);
				found = 1;
				addr->valid = 0;
				list_del_rcu(&addr->list);
				break;
			}
		}
		spin_unlock_bh(&net->sctp.local_addr_lock);
		if (found)
			kfree_rcu(addr, rcu);
		break;
	}

	return NOTIFY_DONE;
}
