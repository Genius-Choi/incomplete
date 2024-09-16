static void addrconf_verify_work(struct work_struct *w)
{
	rtnl_lock();
	addrconf_verify_rtnl();
	rtnl_unlock();
}
