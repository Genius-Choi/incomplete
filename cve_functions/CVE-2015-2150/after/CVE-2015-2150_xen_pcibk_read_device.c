static int xen_pcibk_read_device(struct pci_dev *dev, int offset,
			       u16 *value, void *data)
{
	*value = dev->device;

	return 0;
}
