ip6_tnl_unlink(struct ip6_tnl_net *ip6n, struct ip6_tnl *t)
{
	struct ip6_tnl **tp;

	for (tp = ip6_tnl_bucket(ip6n, &t->parms); *tp; tp = &(*tp)->next) {
		if (t == *tp) {
			spin_lock_bh(&ip6_tnl_lock);
			*tp = t->next;
			spin_unlock_bh(&ip6_tnl_lock);
			break;
		}
	}
}
