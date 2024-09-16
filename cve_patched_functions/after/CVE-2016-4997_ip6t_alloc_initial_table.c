void *ip6t_alloc_initial_table(const struct xt_table *info)
{
	return xt_alloc_initial_table(ip6t, IP6T);
}
