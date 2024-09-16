static int fpuemu_stat_get(void *data, u64 *val)
{
	int cpu;
	unsigned long sum = 0;
	for_each_online_cpu(cpu) {
		struct mips_fpu_emulator_stats *ps;
		local_t *pv;
		ps = &per_cpu(fpuemustats, cpu);
		pv = (void *)ps + (unsigned long)data;
		sum += local_read(pv);
	}
	*val = sum;
	return 0;
}
