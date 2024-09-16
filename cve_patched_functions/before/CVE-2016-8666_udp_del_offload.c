void udp_del_offload(struct udp_offload *uo)
{
	struct udp_offload_priv __rcu **head = &udp_offload_base;
	struct udp_offload_priv *uo_priv;

	spin_lock(&udp_offload_lock);

	uo_priv = udp_deref_protected(*head);
	for (; uo_priv != NULL;
	     uo_priv = udp_deref_protected(*head)) {
		if (uo_priv->offload == uo) {
			rcu_assign_pointer(*head,
					   udp_deref_protected(uo_priv->next));
			goto unlock;
		}
		head = &uo_priv->next;
	}
	pr_warn("udp_del_offload: didn't find offload for port %d\n", ntohs(uo->port));
unlock:
	spin_unlock(&udp_offload_lock);
	if (uo_priv)
		call_rcu(&uo_priv->rcu, udp_offload_free_routine);
}
