static int xen_pcibk_read_vendor(struct pci_dev *dev, int offset,
			       u16 *value, void *data)
{
	*value = dev->vendor;

	return 0;
}
