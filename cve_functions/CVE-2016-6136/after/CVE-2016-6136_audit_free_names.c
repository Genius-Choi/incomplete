static inline void audit_free_names(struct audit_context *context)
{
	struct audit_names *n, *next;

	list_for_each_entry_safe(n, next, &context->names_list, list) {
		list_del(&n->list);
		if (n->name)
			putname(n->name);
		if (n->should_free)
			kfree(n);
	}
	context->name_count = 0;
	path_put(&context->pwd);
	context->pwd.dentry = NULL;
	context->pwd.mnt = NULL;
}
