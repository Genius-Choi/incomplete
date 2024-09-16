void bond_select_active_slave(struct bonding *bond)
{
	struct slave *best_slave;
	int rv;

	best_slave = bond_find_best_slave(bond);
	if (best_slave != bond->curr_active_slave) {
		bond_change_active_slave(bond, best_slave);
		rv = bond_set_carrier(bond);
		if (!rv)
			return;

		if (netif_carrier_ok(bond->dev)) {
			pr_info("%s: first active interface up!\n",
				bond->dev->name);
		} else {
			pr_info("%s: now running without any active interface !\n",
				bond->dev->name);
		}
	}
}
