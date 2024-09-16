static struct user_namespace *userns_owner(struct ns_common *ns)
{
	return to_user_ns(ns)->parent;
}
