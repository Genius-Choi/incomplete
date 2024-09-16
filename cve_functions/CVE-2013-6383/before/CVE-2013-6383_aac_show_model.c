static ssize_t aac_show_model(struct device *device,
			      struct device_attribute *attr, char *buf)
{
	struct aac_dev *dev = (struct aac_dev*)class_to_shost(device)->hostdata;
	int len;

	if (dev->supplement_adapter_info.AdapterTypeText[0]) {
		char * cp = dev->supplement_adapter_info.AdapterTypeText;
		while (*cp && *cp != ' ')
			++cp;
		while (*cp == ' ')
			++cp;
		len = snprintf(buf, PAGE_SIZE, "%s\n", cp);
	} else
		len = snprintf(buf, PAGE_SIZE, "%s\n",
		  aac_drivers[dev->cardtype].model);
	return len;
}
