static void check_irq_off(void)
{
	BUG_ON(!irqs_disabled());
}
