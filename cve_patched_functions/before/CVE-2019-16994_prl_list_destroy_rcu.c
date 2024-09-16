static void prl_list_destroy_rcu(struct rcu_head *head)
{
	struct ip_tunnel_prl_entry *p, *n;

	p = container_of(head, struct ip_tunnel_prl_entry, rcu_head);
	do {
		n = rcu_dereference_protected(p->next, 1);
		kfree(p);
		p = n;
	} while (p);
}
