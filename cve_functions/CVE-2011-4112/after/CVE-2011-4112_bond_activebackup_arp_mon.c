void bond_activebackup_arp_mon(struct work_struct *work)
{
	struct bonding *bond = container_of(work, struct bonding,
					    arp_work.work);
	bool should_notify_peers = false;
	int delta_in_ticks;

	read_lock(&bond->lock);

	if (bond->kill_timers)
		goto out;

	delta_in_ticks = msecs_to_jiffies(bond->params.arp_interval);

	if (bond->slave_cnt == 0)
		goto re_arm;

	should_notify_peers = bond_should_notify_peers(bond);

	if (bond_ab_arp_inspect(bond, delta_in_ticks)) {
		read_unlock(&bond->lock);
		rtnl_lock();
		read_lock(&bond->lock);

		bond_ab_arp_commit(bond, delta_in_ticks);

		read_unlock(&bond->lock);
		rtnl_unlock();
		read_lock(&bond->lock);
	}

	bond_ab_arp_probe(bond);

re_arm:
	if (bond->params.arp_interval)
		queue_delayed_work(bond->wq, &bond->arp_work, delta_in_ticks);
out:
	read_unlock(&bond->lock);

	if (should_notify_peers) {
		rtnl_lock();
		netdev_bonding_change(bond->dev, NETDEV_NOTIFY_PEERS);
		rtnl_unlock();
	}
}
