static struct rb_node *__key_user_next(struct user_namespace *user_ns, struct rb_node *n)
{
	while (n) {
		struct key_user *user = rb_entry(n, struct key_user, node);
		if (kuid_has_mapping(user_ns, user->uid))
			break;
		n = rb_next(n);
	}
	return n;
}
