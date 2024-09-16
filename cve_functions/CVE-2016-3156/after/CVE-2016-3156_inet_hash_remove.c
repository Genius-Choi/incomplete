static void inet_hash_remove(struct in_ifaddr *ifa)
{
	ASSERT_RTNL();
	hlist_del_init_rcu(&ifa->hash);
}
