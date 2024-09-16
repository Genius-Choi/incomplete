void xt_free_table_info(struct xt_table_info *info)
{
	int cpu;

	if (info->jumpstack != NULL) {
		for_each_possible_cpu(cpu)
			kvfree(info->jumpstack[cpu]);
		kvfree(info->jumpstack);
	}

	kvfree(info);
}
