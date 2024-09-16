static void perf_duration_warn(struct irq_work *w)
{
	u64 allowed_ns = ACCESS_ONCE(perf_sample_allowed_ns);
	u64 avg_local_sample_len;
	u64 local_samples_len;

	local_samples_len = __this_cpu_read(running_sample_length);
	avg_local_sample_len = local_samples_len/NR_ACCUMULATED_SAMPLES;

	printk_ratelimited(KERN_WARNING
			"perf interrupt took too long (%lld > %lld), lowering "
			"kernel.perf_event_max_sample_rate to %d\n",
			avg_local_sample_len, allowed_ns >> 1,
			sysctl_perf_event_sample_rate);
}
