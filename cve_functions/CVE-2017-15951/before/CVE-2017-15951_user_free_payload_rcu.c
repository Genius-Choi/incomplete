static void user_free_payload_rcu(struct rcu_head *head)
{
	struct user_key_payload *payload;

	payload = container_of(head, struct user_key_payload, rcu);
	kzfree(payload);
}
