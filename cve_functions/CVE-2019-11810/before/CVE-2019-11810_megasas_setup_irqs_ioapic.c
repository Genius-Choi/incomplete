megasas_setup_irqs_ioapic(struct megasas_instance *instance)
{
	struct pci_dev *pdev;

	pdev = instance->pdev;
	instance->irq_context[0].instance = instance;
	instance->irq_context[0].MSIxIndex = 0;
	if (request_irq(pci_irq_vector(pdev, 0),
			instance->instancet->service_isr, IRQF_SHARED,
			"megasas", &instance->irq_context[0])) {
		dev_err(&instance->pdev->dev,
				"Failed to register IRQ from %s %d\n",
				__func__, __LINE__);
		return -1;
	}
	return 0;
}
