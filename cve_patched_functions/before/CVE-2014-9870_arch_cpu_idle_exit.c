void arch_cpu_idle_exit(void)
{
	ledtrig_cpu(CPU_LED_IDLE_END);
}
