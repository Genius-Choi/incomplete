static struct rb_node *key_user_first(struct user_namespace *user_ns, struct rb_root *r)
{
	struct rb_node *n = rb_first(r);
	return __key_user_next(user_ns, n);
}
