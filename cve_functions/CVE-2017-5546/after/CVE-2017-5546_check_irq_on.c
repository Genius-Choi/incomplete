static void check_irq_on(void)
{
	BUG_ON(irqs_disabled());
}
