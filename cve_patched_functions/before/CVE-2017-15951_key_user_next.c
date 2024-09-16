static struct rb_node *key_user_next(struct user_namespace *user_ns, struct rb_node *n)
{
	return __key_user_next(user_ns, rb_next(n));
}
