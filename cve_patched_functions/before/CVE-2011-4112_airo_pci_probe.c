static int __devinit airo_pci_probe(struct pci_dev *pdev,
				    const struct pci_device_id *pent)
{
	struct net_device *dev;

	if (pci_enable_device(pdev))
		return -ENODEV;
	pci_set_master(pdev);

	if (pdev->device == 0x5000 || pdev->device == 0xa504)
			dev = _init_airo_card(pdev->irq, pdev->resource[0].start, 0, pdev, &pdev->dev);
	else
			dev = _init_airo_card(pdev->irq, pdev->resource[2].start, 0, pdev, &pdev->dev);
	if (!dev) {
		pci_disable_device(pdev);
		return -ENODEV;
	}

	pci_set_drvdata(pdev, dev);
	return 0;
}
