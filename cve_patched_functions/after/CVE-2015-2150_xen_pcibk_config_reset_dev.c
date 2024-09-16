void xen_pcibk_config_reset_dev(struct pci_dev *dev)
{
	struct xen_pcibk_dev_data *dev_data = pci_get_drvdata(dev);
	const struct config_field_entry *cfg_entry;
	const struct config_field *field;

	dev_dbg(&dev->dev, "resetting virtual configuration space\n");
	if (!dev_data)
		return;

	list_for_each_entry(cfg_entry, &dev_data->config_fields, list) {
		field = cfg_entry->field;

		if (field->reset)
			field->reset(dev, OFFSET(cfg_entry), cfg_entry->data);
	}
}
