static bool bond_should_notify_peers(struct bonding *bond)
{
	struct slave *slave = bond->curr_active_slave;

	pr_debug("bond_should_notify_peers: bond %s slave %s\n",
		 bond->dev->name, slave ? slave->dev->name : "NULL");

	if (!slave || !bond->send_peer_notif ||
	    test_bit(__LINK_STATE_LINKWATCH_PENDING, &slave->dev->state))
		return false;

	bond->send_peer_notif--;
	return true;
}
