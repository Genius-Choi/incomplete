static void prl_list_destroy_rcu(struct rcu_head *head)
{
	struct ip_tunnel_prl_entry *p, *n;

	p = container_of(head, struct ip_tunnel_prl_entry, rcu_head);
	do {
		n = p->next;
		kfree(p);
		p = n;
	} while (p);
}
