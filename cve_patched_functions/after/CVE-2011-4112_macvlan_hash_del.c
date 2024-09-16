static void macvlan_hash_del(struct macvlan_dev *vlan, bool sync)
{
	hlist_del_rcu(&vlan->hlist);
	if (sync)
		synchronize_rcu();
}
