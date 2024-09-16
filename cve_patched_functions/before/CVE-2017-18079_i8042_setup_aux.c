static int __init i8042_setup_aux(void)
{
	int (*aux_enable)(void);
	int error;
	int i;

	if (i8042_check_aux())
		return -ENODEV;

	if (i8042_nomux || i8042_check_mux()) {
		error = i8042_create_aux_port(-1);
		if (error)
			goto err_free_ports;
		aux_enable = i8042_enable_aux_port;
	} else {
		for (i = 0; i < I8042_NUM_MUX_PORTS; i++) {
			error = i8042_create_aux_port(i);
			if (error)
				goto err_free_ports;
		}
		aux_enable = i8042_enable_mux_ports;
	}

	error = request_irq(I8042_AUX_IRQ, i8042_interrupt, IRQF_SHARED,
			    "i8042", i8042_platform_device);
	if (error)
		goto err_free_ports;

	if (aux_enable())
		goto err_free_irq;

	i8042_aux_irq_registered = true;
	return 0;

 err_free_irq:
	free_irq(I8042_AUX_IRQ, i8042_platform_device);
 err_free_ports:
	i8042_free_aux_ports();
	return error;
}
