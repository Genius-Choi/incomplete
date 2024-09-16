static void *bar_init(struct pci_dev *dev, int offset)
{
	struct pci_bar_info *bar = kmalloc(sizeof(*bar), GFP_KERNEL);

	if (!bar)
		return ERR_PTR(-ENOMEM);

	read_dev_bar(dev, bar, offset, ~0);
	bar->which = 0;

	return bar;
}
