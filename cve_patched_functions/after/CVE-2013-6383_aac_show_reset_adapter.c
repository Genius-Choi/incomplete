static ssize_t aac_show_reset_adapter(struct device *device,
				      struct device_attribute *attr,
				      char *buf)
{
	struct aac_dev *dev = (struct aac_dev*)class_to_shost(device)->hostdata;
	int len, tmp;

	tmp = aac_adapter_check_health(dev);
	if ((tmp == 0) && dev->in_reset)
		tmp = -EBUSY;
	len = snprintf(buf, PAGE_SIZE, "0x%x\n", tmp);
	return len;
}
