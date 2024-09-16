static int bar_read(struct pci_dev *dev, int offset, u32 * value, void *data)
{
	struct pci_bar_info *bar = data;

	if (unlikely(!bar)) {
		pr_warn(DRV_NAME ": driver data not found for %s\n",
		       pci_name(dev));
		return XEN_PCI_ERR_op_failed;
	}

	*value = bar->which ? bar->len_val : bar->val;

	return 0;
}
