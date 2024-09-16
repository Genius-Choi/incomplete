int sysctl_perm(struct ctl_table_root *root, struct ctl_table *table, int op)
{
	int mode;

	if (root->permissions)
		mode = root->permissions(root, current->nsproxy, table);
	else
		mode = table->mode;

	return test_perm(mode, op);
}
