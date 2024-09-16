static void dwc3_reset_gadget(struct dwc3 *dwc)
{
	if (!dwc->gadget_driver)
		return;

	if (dwc->gadget.speed != USB_SPEED_UNKNOWN) {
		spin_unlock(&dwc->lock);
		usb_gadget_udc_reset(&dwc->gadget, dwc->gadget_driver);
		spin_lock(&dwc->lock);
	}
}
