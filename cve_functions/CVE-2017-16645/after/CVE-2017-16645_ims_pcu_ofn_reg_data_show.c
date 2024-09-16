static ssize_t ims_pcu_ofn_reg_data_show(struct device *dev,
					 struct device_attribute *dattr,
					 char *buf)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct ims_pcu *pcu = usb_get_intfdata(intf);
	int error;
	u8 data;

	mutex_lock(&pcu->cmd_mutex);
	error = ims_pcu_read_ofn_config(pcu, pcu->ofn_reg_addr, &data);
	mutex_unlock(&pcu->cmd_mutex);

	if (error)
		return error;

	return scnprintf(buf, PAGE_SIZE, "%x\n", data);
}
