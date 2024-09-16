static void ipip_tunnel_unlink(struct ipip_net *ipn, struct ip_tunnel *t)
{
	struct ip_tunnel **tp;

	for (tp = ipip_bucket(ipn, t); *tp; tp = &(*tp)->next) {
		if (t == *tp) {
			spin_lock_bh(&ipip_lock);
			*tp = t->next;
			spin_unlock_bh(&ipip_lock);
			break;
		}
	}
}
