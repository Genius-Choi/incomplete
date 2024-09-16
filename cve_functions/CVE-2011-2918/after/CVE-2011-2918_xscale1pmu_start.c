xscale1pmu_start(void)
{
	unsigned long flags, val;

	raw_spin_lock_irqsave(&pmu_lock, flags);
	val = xscale1pmu_read_pmnc();
	val |= XSCALE_PMU_ENABLE;
	xscale1pmu_write_pmnc(val);
	raw_spin_unlock_irqrestore(&pmu_lock, flags);
}
