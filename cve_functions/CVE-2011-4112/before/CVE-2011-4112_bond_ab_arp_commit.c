static void bond_ab_arp_commit(struct bonding *bond, int delta_in_ticks)
{
	struct slave *slave;
	int i;
	unsigned long trans_start;

	bond_for_each_slave(bond, slave, i) {
		switch (slave->new_link) {
		case BOND_LINK_NOCHANGE:
			continue;

		case BOND_LINK_UP:
			trans_start = dev_trans_start(slave->dev);
			if ((!bond->curr_active_slave &&
			     time_in_range(jiffies,
					   trans_start - delta_in_ticks,
					   trans_start + delta_in_ticks)) ||
			    bond->curr_active_slave != slave) {
				slave->link = BOND_LINK_UP;
				bond->current_arp_slave = NULL;

				pr_info("%s: link status definitely up for interface %s.\n",
					bond->dev->name, slave->dev->name);

				if (!bond->curr_active_slave ||
				    (slave == bond->primary_slave))
					goto do_failover;

			}

			continue;

		case BOND_LINK_DOWN:
			if (slave->link_failure_count < UINT_MAX)
				slave->link_failure_count++;

			slave->link = BOND_LINK_DOWN;
			bond_set_slave_inactive_flags(slave);

			pr_info("%s: link status definitely down for interface %s, disabling it\n",
				bond->dev->name, slave->dev->name);

			if (slave == bond->curr_active_slave) {
				bond->current_arp_slave = NULL;
				goto do_failover;
			}

			continue;

		default:
			pr_err("%s: impossible: new_link %d on slave %s\n",
			       bond->dev->name, slave->new_link,
			       slave->dev->name);
			continue;
		}

do_failover:
		ASSERT_RTNL();
		block_netpoll_tx();
		write_lock_bh(&bond->curr_slave_lock);
		bond_select_active_slave(bond);
		write_unlock_bh(&bond->curr_slave_lock);
		unblock_netpoll_tx();
	}

	bond_set_carrier(bond);
}
