static void ipip6_tunnel_unlink(struct sit_net *sitn, struct ip_tunnel *t)
{
	struct ip_tunnel **tp;

	for (tp = ipip6_bucket(sitn, t); *tp; tp = &(*tp)->next) {
		if (t == *tp) {
			spin_lock_bh(&ipip6_lock);
			*tp = t->next;
			spin_unlock_bh(&ipip6_lock);
			break;
		}
	}
}
