static ssize_t aac_show_monitor_version(struct device *device,
					struct device_attribute *attr,
					char *buf)
{
	struct aac_dev *dev = (struct aac_dev*)class_to_shost(device)->hostdata;
	int len, tmp;

	tmp = le32_to_cpu(dev->adapter_info.monitorrev);
	len = snprintf(buf, PAGE_SIZE, "%d.%d-%d[%d]\n",
	  tmp >> 24, (tmp >> 16) & 0xff, tmp & 0xff,
	  le32_to_cpu(dev->adapter_info.monitorbuild));
	return len;
}
