static inline int kvm_tsc_changes_freq(void)
{
	int cpu = get_cpu();
	int ret = !boot_cpu_has(X86_FEATURE_CONSTANT_TSC) &&
		  cpufreq_quick_get(cpu) != 0;
	put_cpu();
	return ret;
}
