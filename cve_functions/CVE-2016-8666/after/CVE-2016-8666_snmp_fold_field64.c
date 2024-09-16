u64 snmp_fold_field64(void __percpu *mib, int offt, size_t syncp_offset)
{
	u64 res = 0;
	int cpu;

	for_each_possible_cpu(cpu) {
		res += snmp_get_cpu_field64(mib, cpu, offt, syncp_offset);
	}
	return res;
}
