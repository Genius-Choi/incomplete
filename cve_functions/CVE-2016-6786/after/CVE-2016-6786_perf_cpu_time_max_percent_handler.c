int perf_cpu_time_max_percent_handler(struct ctl_table *table, int write,
				void __user *buffer, size_t *lenp,
				loff_t *ppos)
{
	int ret = proc_dointvec(table, write, buffer, lenp, ppos);

	if (ret || !write)
		return ret;

	update_perf_cpu_limits();

	return 0;
}
