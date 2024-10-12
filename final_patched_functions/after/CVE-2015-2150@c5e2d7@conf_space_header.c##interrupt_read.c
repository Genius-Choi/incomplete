static int interrupt_read(struct pci_dev *dev, int offset, u8 * value,
			  void *data)
{
	*value = (u8) dev->irq;

	return 0;
}
