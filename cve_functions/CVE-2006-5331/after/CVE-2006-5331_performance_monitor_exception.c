void performance_monitor_exception(struct pt_regs *regs)
{
	perf_irq(regs);
}
