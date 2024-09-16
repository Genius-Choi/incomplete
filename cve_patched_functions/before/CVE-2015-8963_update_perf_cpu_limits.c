static void update_perf_cpu_limits(void)
{
	u64 tmp = perf_sample_period_ns;

	tmp *= sysctl_perf_cpu_time_max_percent;
	do_div(tmp, 100);
	ACCESS_ONCE(perf_sample_allowed_ns) = tmp;
}
