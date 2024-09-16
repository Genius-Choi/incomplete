u64 snmp_get_cpu_field(void __percpu *mib, int cpu, int offt)
{
	return  *(((unsigned long *)per_cpu_ptr(mib, cpu)) + offt);
}
