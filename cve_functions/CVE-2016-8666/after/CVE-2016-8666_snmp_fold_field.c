unsigned long snmp_fold_field(void __percpu *mib, int offt)
{
	unsigned long res = 0;
	int i;

	for_each_possible_cpu(i)
		res += snmp_get_cpu_field(mib, i, offt);
	return res;
}
