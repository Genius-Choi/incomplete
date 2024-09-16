static void bond_work_cancel_all(struct bonding *bond)
{
	write_lock_bh(&bond->lock);
	bond->kill_timers = 1;
	write_unlock_bh(&bond->lock);

	if (bond->params.miimon && delayed_work_pending(&bond->mii_work))
		cancel_delayed_work(&bond->mii_work);

	if (bond->params.arp_interval && delayed_work_pending(&bond->arp_work))
		cancel_delayed_work(&bond->arp_work);

	if (bond->params.mode == BOND_MODE_ALB &&
	    delayed_work_pending(&bond->alb_work))
		cancel_delayed_work(&bond->alb_work);

	if (bond->params.mode == BOND_MODE_8023AD &&
	    delayed_work_pending(&bond->ad_work))
		cancel_delayed_work(&bond->ad_work);

	if (delayed_work_pending(&bond->mcast_work))
		cancel_delayed_work(&bond->mcast_work);
}
