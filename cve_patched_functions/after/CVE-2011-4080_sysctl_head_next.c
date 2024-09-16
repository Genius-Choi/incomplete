struct ctl_table_header *sysctl_head_next(struct ctl_table_header *prev)
{
	return __sysctl_head_next(current->nsproxy, prev);
}
