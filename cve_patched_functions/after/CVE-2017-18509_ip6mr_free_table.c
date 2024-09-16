static void ip6mr_free_table(struct mr6_table *mrt)
{
	del_timer_sync(&mrt->ipmr_expire_timer);
	mroute_clean_tables(mrt, true);
	kfree(mrt);
}
