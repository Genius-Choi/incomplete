u64 snmp_get_cpu_field64(void __percpu *mib, int cpu, int offt,
			 size_t syncp_offset)
{
	void *bhptr;
	struct u64_stats_sync *syncp;
	u64 v;
	unsigned int start;

	bhptr = per_cpu_ptr(mib, cpu);
	syncp = (struct u64_stats_sync *)(bhptr + syncp_offset);
	do {
		start = u64_stats_fetch_begin_irq(syncp);
		v = *(((u64 *)bhptr) + offt);
	} while (u64_stats_fetch_retry_irq(syncp, start));

	return v;
}
