armpmu_disable_percpu_irq(void *data)
{
	unsigned int irq = *(unsigned int *)data;
	disable_percpu_irq(irq);
}
