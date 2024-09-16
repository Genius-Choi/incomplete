static int ims_pcu_line_setup(struct ims_pcu *pcu)
{
	struct usb_host_interface *interface = pcu->ctrl_intf->cur_altsetting;
	struct usb_cdc_line_coding *line = (void *)pcu->cmd_buf;
	int error;

	memset(line, 0, sizeof(*line));
	line->dwDTERate = cpu_to_le32(57600);
	line->bDataBits = 8;

	error = usb_control_msg(pcu->udev, usb_sndctrlpipe(pcu->udev, 0),
				USB_CDC_REQ_SET_LINE_CODING,
				USB_TYPE_CLASS | USB_RECIP_INTERFACE,
				0, interface->desc.bInterfaceNumber,
				line, sizeof(struct usb_cdc_line_coding),
				5000);
	if (error < 0) {
		dev_err(pcu->dev, "Failed to set line coding, error: %d\n",
			error);
		return error;
	}

	error = usb_control_msg(pcu->udev, usb_sndctrlpipe(pcu->udev, 0),
				USB_CDC_REQ_SET_CONTROL_LINE_STATE,
				USB_TYPE_CLASS | USB_RECIP_INTERFACE,
				0x03, interface->desc.bInterfaceNumber,
				NULL, 0, 5000);
	if (error < 0) {
		dev_err(pcu->dev, "Failed to set line state, error: %d\n",
			error);
		return error;
	}

	return 0;
}
