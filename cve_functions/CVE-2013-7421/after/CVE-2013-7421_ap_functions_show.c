static ssize_t ap_functions_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct ap_device *ap_dev = to_ap_dev(dev);
	return snprintf(buf, PAGE_SIZE, "0x%08X\n", ap_dev->functions);
}
