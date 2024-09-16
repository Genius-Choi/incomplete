static inline key_serial_t key_node_serial(struct rb_node *n)
{
	struct key *key = rb_entry(n, struct key, serial_node);
	return key->serial;
}
