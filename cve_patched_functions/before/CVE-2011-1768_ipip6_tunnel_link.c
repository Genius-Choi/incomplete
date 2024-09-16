static void ipip6_tunnel_link(struct sit_net *sitn, struct ip_tunnel *t)
{
	struct ip_tunnel **tp = ipip6_bucket(sitn, t);

	spin_lock_bh(&ipip6_lock);
	t->next = *tp;
	rcu_assign_pointer(*tp, t);
	spin_unlock_bh(&ipip6_lock);
}
