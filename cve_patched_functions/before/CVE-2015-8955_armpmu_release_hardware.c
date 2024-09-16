armpmu_release_hardware(struct arm_pmu *armpmu)
{
	int irq;
	unsigned int i, irqs;
	struct platform_device *pmu_device = armpmu->plat_device;

	irqs = min(pmu_device->num_resources, num_possible_cpus());
	if (!irqs)
		return;

	irq = platform_get_irq(pmu_device, 0);
	if (irq <= 0)
		return;

	if (irq_is_percpu(irq)) {
		on_each_cpu(armpmu_disable_percpu_irq, &irq, 1);
		free_percpu_irq(irq, &cpu_hw_events);
	} else {
		for (i = 0; i < irqs; ++i) {
			if (!cpumask_test_and_clear_cpu(i, &armpmu->active_irqs))
				continue;
			irq = platform_get_irq(pmu_device, i);
			if (irq > 0)
				free_irq(irq, armpmu);
		}
	}
}
