static void ipgre_tunnel_unlink(struct ipgre_net *ign, struct ip_tunnel *t)
{
	struct ip_tunnel **tp;

	for (tp = ipgre_bucket(ign, t); *tp; tp = &(*tp)->next) {
		if (t == *tp) {
			spin_lock_bh(&ipgre_lock);
			*tp = t->next;
			spin_unlock_bh(&ipgre_lock);
			break;
		}
	}
}
