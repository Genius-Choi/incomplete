static void prl_entry_destroy_rcu(struct rcu_head *head)
{
	kfree(container_of(head, struct ip_tunnel_prl_entry, rcu_head));
}
