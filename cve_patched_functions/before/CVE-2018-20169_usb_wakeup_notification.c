void usb_wakeup_notification(struct usb_device *hdev,
		unsigned int portnum)
{
	struct usb_hub *hub;
	struct usb_port *port_dev;

	if (!hdev)
		return;

	hub = usb_hub_to_struct_hub(hdev);
	if (hub) {
		port_dev = hub->ports[portnum - 1];
		if (port_dev && port_dev->child)
			pm_wakeup_event(&port_dev->child->dev, 0);

		set_bit(portnum, hub->wakeup_bits);
		kick_hub_wq(hub);
	}
}
