ip6_tnl_link(struct ip6_tnl_net *ip6n, struct ip6_tnl *t)
{
	struct ip6_tnl **tp = ip6_tnl_bucket(ip6n, &t->parms);

	spin_lock_bh(&ip6_tnl_lock);
	t->next = *tp;
	rcu_assign_pointer(*tp, t);
	spin_unlock_bh(&ip6_tnl_lock);
}
