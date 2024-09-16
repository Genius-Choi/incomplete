static struct key *find_ge_key(struct seq_file *p, key_serial_t id)
{
	struct user_namespace *user_ns = seq_user_ns(p);
	struct rb_node *n = key_serial_tree.rb_node;
	struct key *minkey = NULL;

	while (n) {
		struct key *key = rb_entry(n, struct key, serial_node);
		if (id < key->serial) {
			if (!minkey || minkey->serial > key->serial)
				minkey = key;
			n = n->rb_left;
		} else if (id > key->serial) {
			n = n->rb_right;
		} else {
			minkey = key;
			break;
		}
		key = NULL;
	}

	if (!minkey)
		return NULL;

	for (;;) {
		if (kuid_has_mapping(user_ns, minkey->user->uid))
			return minkey;
		n = rb_next(&minkey->serial_node);
		if (!n)
			return NULL;
		minkey = rb_entry(n, struct key, serial_node);
	}
}
