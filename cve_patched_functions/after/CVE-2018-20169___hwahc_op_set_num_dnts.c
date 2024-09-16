static int __hwahc_op_set_num_dnts(struct wusbhc *wusbhc, u8 interval, u8 slots)
{
	struct hwahc *hwahc = container_of(wusbhc, struct hwahc, wusbhc);
	struct wahc *wa = &hwahc->wa;

	return usb_control_msg(wa->usb_dev, usb_sndctrlpipe(wa->usb_dev, 0),
			WUSB_REQ_SET_NUM_DNTS,
			USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			interval << 8 | slots,
			wa->usb_iface->cur_altsetting->desc.bInterfaceNumber,
			NULL, 0, USB_CTRL_SET_TIMEOUT);
}
