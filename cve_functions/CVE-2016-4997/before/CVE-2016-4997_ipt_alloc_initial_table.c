void *ipt_alloc_initial_table(const struct xt_table *info)
{
	return xt_alloc_initial_table(ipt, IPT);
}
