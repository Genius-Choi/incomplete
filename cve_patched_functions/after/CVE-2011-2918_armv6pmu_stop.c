armv6pmu_stop(void)
{
	unsigned long flags, val;

	raw_spin_lock_irqsave(&pmu_lock, flags);
	val = armv6_pmcr_read();
	val &= ~ARMV6_PMCR_ENABLE;
	armv6_pmcr_write(val);
	raw_spin_unlock_irqrestore(&pmu_lock, flags);
}
