int hugetlb_treat_movable_handler(struct ctl_table *table, int write,
			void __user *buffer,
			size_t *length, loff_t *ppos)
{
	proc_dointvec(table, write, buffer, length, ppos);
	if (hugepages_treat_as_movable)
		htlb_alloc_mask = GFP_HIGHUSER_MOVABLE;
	else
		htlb_alloc_mask = GFP_HIGHUSER;
	return 0;
}
