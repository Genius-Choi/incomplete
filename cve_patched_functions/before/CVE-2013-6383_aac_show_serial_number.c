static ssize_t aac_show_serial_number(struct device *device,
			       struct device_attribute *attr, char *buf)
{
	struct aac_dev *dev = (struct aac_dev*)class_to_shost(device)->hostdata;
	int len = 0;

	if (le32_to_cpu(dev->adapter_info.serial[0]) != 0xBAD0)
		len = snprintf(buf, 16, "%06X\n",
		  le32_to_cpu(dev->adapter_info.serial[0]));
	if (len &&
	  !memcmp(&dev->supplement_adapter_info.MfgPcbaSerialNo[
	    sizeof(dev->supplement_adapter_info.MfgPcbaSerialNo)-len],
	  buf, len-1))
		len = snprintf(buf, 16, "%.*s\n",
		  (int)sizeof(dev->supplement_adapter_info.MfgPcbaSerialNo),
		  dev->supplement_adapter_info.MfgPcbaSerialNo);

	return min(len, 16);
}
