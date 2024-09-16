void arch_cpu_idle_prepare(void)
{
	local_fiq_enable();
}
