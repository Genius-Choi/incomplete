static void bar_reset(struct pci_dev *dev, int offset, void *data)
{
	struct pci_bar_info *bar = data;

	bar->which = 0;
}
