static void bar_release(struct pci_dev *dev, int offset, void *data)
{
	kfree(data);
}
