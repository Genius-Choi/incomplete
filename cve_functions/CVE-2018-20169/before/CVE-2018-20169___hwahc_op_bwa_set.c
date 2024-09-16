static int __hwahc_op_bwa_set(struct wusbhc *wusbhc, s8 stream_index,
			      const struct uwb_mas_bm *mas)
{
	int result;
	struct hwahc *hwahc = container_of(wusbhc, struct hwahc, wusbhc);
	struct wahc *wa = &hwahc->wa;
	struct device *dev = &wa->usb_iface->dev;
	u8 mas_le[UWB_NUM_MAS/8];

	/* Set the stream index */
	result = usb_control_msg(wa->usb_dev, usb_sndctrlpipe(wa->usb_dev, 0),
			WUSB_REQ_SET_STREAM_IDX,
			USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			stream_index,
			wa->usb_iface->cur_altsetting->desc.bInterfaceNumber,
			NULL, 0, USB_CTRL_SET_TIMEOUT);
	if (result < 0) {
		dev_err(dev, "Cannot set WUSB stream index: %d\n", result);
		goto out;
	}
	uwb_mas_bm_copy_le(mas_le, mas);
	/* Set the MAS allocation */
	result = usb_control_msg(wa->usb_dev, usb_sndctrlpipe(wa->usb_dev, 0),
			WUSB_REQ_SET_WUSB_MAS,
			USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			0, wa->usb_iface->cur_altsetting->desc.bInterfaceNumber,
			mas_le, 32, USB_CTRL_SET_TIMEOUT);
	if (result < 0)
		dev_err(dev, "Cannot set WUSB MAS allocation: %d\n", result);
out:
	return result;
}
