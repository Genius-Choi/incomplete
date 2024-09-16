static void inetpeer_free_rcu(struct rcu_head *head)
{
	kmem_cache_free(peer_cachep, container_of(head, struct inet_peer, rcu));
}
