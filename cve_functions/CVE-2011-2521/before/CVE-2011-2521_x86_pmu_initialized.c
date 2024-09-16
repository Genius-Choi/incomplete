static inline int x86_pmu_initialized(void)
{
	return x86_pmu.handle_irq != NULL;
}
