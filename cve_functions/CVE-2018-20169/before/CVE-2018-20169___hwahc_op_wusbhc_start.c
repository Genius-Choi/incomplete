static int __hwahc_op_wusbhc_start(struct wusbhc *wusbhc)
{
	int result;
	struct hwahc *hwahc = container_of(wusbhc, struct hwahc, wusbhc);
	struct device *dev = &hwahc->wa.usb_iface->dev;

	result = __wa_set_feature(&hwahc->wa, WA_ENABLE);
	if (result < 0) {
		dev_err(dev, "error commanding HC to start: %d\n", result);
		goto error_stop;
	}
	result = __wa_wait_status(&hwahc->wa, WA_ENABLE, WA_ENABLE);
	if (result < 0) {
		dev_err(dev, "error waiting for HC to start: %d\n", result);
		goto error_stop;
	}
	result = wa_nep_arm(&hwahc->wa, GFP_KERNEL);
	if (result < 0) {
		dev_err(dev, "cannot listen to notifications: %d\n", result);
		goto error_stop;
	}
	/*
	 * If WUSB_QUIRK_ALEREON_HWA_DISABLE_XFER_NOTIFICATIONS is set,
	 *  disable transfer notifications.
	 */
	if (hwahc->wa.quirks &
		WUSB_QUIRK_ALEREON_HWA_DISABLE_XFER_NOTIFICATIONS) {
		struct usb_host_interface *cur_altsetting =
			hwahc->wa.usb_iface->cur_altsetting;

		result = usb_control_msg(hwahc->wa.usb_dev,
				usb_sndctrlpipe(hwahc->wa.usb_dev, 0),
				WA_REQ_ALEREON_DISABLE_XFER_NOTIFICATIONS,
				USB_DIR_OUT | USB_TYPE_VENDOR |
					USB_RECIP_INTERFACE,
				WA_REQ_ALEREON_FEATURE_SET,
				cur_altsetting->desc.bInterfaceNumber,
				NULL, 0,
				USB_CTRL_SET_TIMEOUT);
		/*
		 * If we successfully sent the control message, start DTI here
		 * because no transfer notifications will be received which is
		 * where DTI is normally started.
		 */
		if (result == 0)
			result = wa_dti_start(&hwahc->wa);
		else
			result = 0;	/* OK.  Continue normally. */

		if (result < 0) {
			dev_err(dev, "cannot start DTI: %d\n", result);
			goto error_dti_start;
		}
	}

	return result;

error_dti_start:
	wa_nep_disarm(&hwahc->wa);
error_stop:
	__wa_clear_feature(&hwahc->wa, WA_ENABLE);
	return result;
}
