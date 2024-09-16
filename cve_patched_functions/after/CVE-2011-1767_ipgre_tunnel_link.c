static void ipgre_tunnel_link(struct ipgre_net *ign, struct ip_tunnel *t)
{
	struct ip_tunnel **tp = ipgre_bucket(ign, t);

	spin_lock_bh(&ipgre_lock);
	t->next = *tp;
	rcu_assign_pointer(*tp, t);
	spin_unlock_bh(&ipgre_lock);
}
