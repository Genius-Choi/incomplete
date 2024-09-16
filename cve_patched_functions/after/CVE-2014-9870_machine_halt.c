void machine_halt(void)
{
	machine_shutdown();
	local_irq_disable();
	while (1);
}
