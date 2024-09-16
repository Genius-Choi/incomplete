static struct rb_node *key_serial_next(struct seq_file *p, struct rb_node *n)
{
	struct user_namespace *user_ns = seq_user_ns(p);

	n = rb_next(n);
	while (n) {
		struct key *key = rb_entry(n, struct key, serial_node);
		if (kuid_has_mapping(user_ns, key->user->uid))
			break;
		n = rb_next(n);
	}
	return n;
}
