int __init __weak arch_probe_nr_irqs(void)
{
	return NR_IRQS_LEGACY;
}
