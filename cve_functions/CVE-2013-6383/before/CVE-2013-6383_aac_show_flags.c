static ssize_t aac_show_flags(struct device *cdev,
			      struct device_attribute *attr, char *buf)
{
	int len = 0;
	struct aac_dev *dev = (struct aac_dev*)class_to_shost(cdev)->hostdata;

	if (nblank(dprintk(x)))
		len = snprintf(buf, PAGE_SIZE, "dprintk\n");
#ifdef AAC_DETAILED_STATUS_INFO
	len += snprintf(buf + len, PAGE_SIZE - len,
			"AAC_DETAILED_STATUS_INFO\n");
#endif
	if (dev->raw_io_interface && dev->raw_io_64)
		len += snprintf(buf + len, PAGE_SIZE - len,
				"SAI_READ_CAPACITY_16\n");
	if (dev->jbod)
		len += snprintf(buf + len, PAGE_SIZE - len, "SUPPORTED_JBOD\n");
	if (dev->supplement_adapter_info.SupportedOptions2 &
		AAC_OPTION_POWER_MANAGEMENT)
		len += snprintf(buf + len, PAGE_SIZE - len,
				"SUPPORTED_POWER_MANAGEMENT\n");
	if (dev->msi)
		len += snprintf(buf + len, PAGE_SIZE - len, "PCI_HAS_MSI\n");
	return len;
}
