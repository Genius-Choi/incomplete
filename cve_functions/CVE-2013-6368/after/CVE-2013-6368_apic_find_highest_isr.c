static inline int apic_find_highest_isr(struct kvm_lapic *apic)
{
	int result;

	/* Note that isr_count is always 1 with vid enabled */
	if (!apic->isr_count)
		return -1;
	if (likely(apic->highest_isr_cache != -1))
		return apic->highest_isr_cache;

	result = find_highest_vector(apic->regs + APIC_ISR);
	ASSERT(result == -1 || result >= 16);

	return result;
}
