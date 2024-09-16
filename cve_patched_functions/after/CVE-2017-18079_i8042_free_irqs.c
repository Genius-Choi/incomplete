static void i8042_free_irqs(void)
{
	if (i8042_aux_irq_registered)
		free_irq(I8042_AUX_IRQ, i8042_platform_device);
	if (i8042_kbd_irq_registered)
		free_irq(I8042_KBD_IRQ, i8042_platform_device);

	i8042_aux_irq_registered = i8042_kbd_irq_registered = false;
}
