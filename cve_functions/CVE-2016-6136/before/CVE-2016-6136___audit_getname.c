void __audit_getname(struct filename *name)
{
	struct audit_context *context = current->audit_context;
	struct audit_names *n;

	if (!context->in_syscall)
		return;

	n = audit_alloc_name(context, AUDIT_TYPE_UNKNOWN);
	if (!n)
		return;

	n->name = name;
	n->name_len = AUDIT_NAME_FULL;
	name->aname = n;
	name->refcnt++;

	if (!context->pwd.dentry)
		get_fs_pwd(current->fs, &context->pwd);
}
