unsigned long snmp_fold_field(void __percpu *mib[], int offt)
{
	unsigned long res = 0;
	int i;

	for_each_possible_cpu(i) {
		res += *(((unsigned long *) per_cpu_ptr(mib[0], i)) + offt);
		res += *(((unsigned long *) per_cpu_ptr(mib[1], i)) + offt);
	}
	return res;
}
