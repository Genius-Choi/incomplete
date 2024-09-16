static void ipip_tunnel_link(struct ipip_net *ipn, struct ip_tunnel *t)
{
	struct ip_tunnel **tp = ipip_bucket(ipn, t);

	spin_lock_bh(&ipip_lock);
	t->next = *tp;
	rcu_assign_pointer(*tp, t);
	spin_unlock_bh(&ipip_lock);
}
