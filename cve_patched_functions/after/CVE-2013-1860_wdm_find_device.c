static struct wdm_device *wdm_find_device(struct usb_interface *intf)
{
	struct wdm_device *desc;

	spin_lock(&wdm_device_list_lock);
	list_for_each_entry(desc, &wdm_device_list, device_list)
		if (desc->intf == intf)
			goto found;
	desc = NULL;
found:
	spin_unlock(&wdm_device_list_lock);

	return desc;
}
