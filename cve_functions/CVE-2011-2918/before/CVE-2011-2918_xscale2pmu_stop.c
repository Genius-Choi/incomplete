xscale2pmu_stop(void)
{
	unsigned long flags, val;

	raw_spin_lock_irqsave(&pmu_lock, flags);
	val = xscale2pmu_read_pmnc();
	val &= ~XSCALE_PMU_ENABLE;
	xscale2pmu_write_pmnc(val);
	raw_spin_unlock_irqrestore(&pmu_lock, flags);
}
