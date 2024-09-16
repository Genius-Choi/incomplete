static void ap_interrupt_handler(struct airq_struct *airq)
{
	inc_irq_stat(IRQIO_APB);
	tasklet_schedule(&ap_tasklet);
}
