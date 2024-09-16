int xen_pcibk_config_init_dev(struct pci_dev *dev)
{
	int err = 0;
	struct xen_pcibk_dev_data *dev_data = pci_get_drvdata(dev);

	dev_dbg(&dev->dev, "initializing virtual configuration space\n");

	INIT_LIST_HEAD(&dev_data->config_fields);

	err = xen_pcibk_config_header_add_fields(dev);
	if (err)
		goto out;

	err = xen_pcibk_config_capability_add_fields(dev);
	if (err)
		goto out;

	err = xen_pcibk_config_quirks_init(dev);

out:
	return err;
}
