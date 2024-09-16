static unsigned long power_of(int cpu)
{
	return cpu_rq(cpu)->cpu_power;
}
