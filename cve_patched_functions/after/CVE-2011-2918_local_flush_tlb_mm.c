void local_flush_tlb_mm(struct mm_struct *mm)
{
	unsigned long flags;
	unsigned int cpu = smp_processor_id();

	if (cpu_context(cpu, mm) == NO_CONTEXT)
		return;

	local_irq_save(flags);

	cpu_context(cpu, mm) = NO_CONTEXT;
	if (mm == current->mm)
		activate_context(mm, cpu);

	local_irq_restore(flags);
}
