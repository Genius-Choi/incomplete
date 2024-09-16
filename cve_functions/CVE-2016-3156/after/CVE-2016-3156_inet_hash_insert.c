static void inet_hash_insert(struct net *net, struct in_ifaddr *ifa)
{
	u32 hash = inet_addr_hash(net, ifa->ifa_local);

	ASSERT_RTNL();
	hlist_add_head_rcu(&ifa->hash, &inet_addr_lst[hash]);
}
