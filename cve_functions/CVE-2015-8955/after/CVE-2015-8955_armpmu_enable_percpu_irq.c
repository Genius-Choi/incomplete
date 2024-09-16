armpmu_enable_percpu_irq(void *data)
{
	unsigned int irq = *(unsigned int *)data;
	enable_percpu_irq(irq, IRQ_TYPE_NONE);
}
