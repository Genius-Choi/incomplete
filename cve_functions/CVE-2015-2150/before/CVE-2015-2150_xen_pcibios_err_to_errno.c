static int xen_pcibios_err_to_errno(int err)
{
	switch (err) {
	case PCIBIOS_SUCCESSFUL:
		return XEN_PCI_ERR_success;
	case PCIBIOS_DEVICE_NOT_FOUND:
		return XEN_PCI_ERR_dev_not_found;
	case PCIBIOS_BAD_REGISTER_NUMBER:
		return XEN_PCI_ERR_invalid_offset;
	case PCIBIOS_FUNC_NOT_SUPPORTED:
		return XEN_PCI_ERR_not_implemented;
	case PCIBIOS_SET_FAILED:
		return XEN_PCI_ERR_access_denied;
	}
	return err;
}
