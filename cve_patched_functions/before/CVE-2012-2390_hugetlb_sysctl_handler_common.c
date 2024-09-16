static int hugetlb_sysctl_handler_common(bool obey_mempolicy,
			 struct ctl_table *table, int write,
			 void __user *buffer, size_t *length, loff_t *ppos)
{
	struct hstate *h = &default_hstate;
	unsigned long tmp;
	int ret;

	tmp = h->max_huge_pages;

	if (write && h->order >= MAX_ORDER)
		return -EINVAL;

	table->data = &tmp;
	table->maxlen = sizeof(unsigned long);
	ret = proc_doulongvec_minmax(table, write, buffer, length, ppos);
	if (ret)
		goto out;

	if (write) {
		NODEMASK_ALLOC(nodemask_t, nodes_allowed,
						GFP_KERNEL | __GFP_NORETRY);
		if (!(obey_mempolicy &&
			       init_nodemask_of_mempolicy(nodes_allowed))) {
			NODEMASK_FREE(nodes_allowed);
			nodes_allowed = &node_states[N_HIGH_MEMORY];
		}
		h->max_huge_pages = set_max_huge_pages(h, tmp, nodes_allowed);

		if (nodes_allowed != &node_states[N_HIGH_MEMORY])
			NODEMASK_FREE(nodes_allowed);
	}
out:
	return ret;
}
