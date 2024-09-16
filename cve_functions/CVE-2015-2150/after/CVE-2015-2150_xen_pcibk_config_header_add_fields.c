int xen_pcibk_config_header_add_fields(struct pci_dev *dev)
{
	int err;

	err = xen_pcibk_config_add_fields(dev, header_common);
	if (err)
		goto out;

	switch (dev->hdr_type) {
	case PCI_HEADER_TYPE_NORMAL:
		err = xen_pcibk_config_add_fields(dev, header_0);
		break;

	case PCI_HEADER_TYPE_BRIDGE:
		err = xen_pcibk_config_add_fields(dev, header_1);
		break;

	default:
		err = -EINVAL;
		pr_err("%s: Unsupported header type %d!\n",
		       pci_name(dev), dev->hdr_type);
		break;
	}

out:
	return err;
}
