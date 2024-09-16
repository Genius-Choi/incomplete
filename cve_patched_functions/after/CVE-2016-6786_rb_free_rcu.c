static void rb_free_rcu(struct rcu_head *rcu_head)
{
	struct ring_buffer *rb;

	rb = container_of(rcu_head, struct ring_buffer, rcu_head);
	rb_free(rb);
}
