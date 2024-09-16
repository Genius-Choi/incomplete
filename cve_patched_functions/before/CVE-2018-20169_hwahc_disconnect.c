static void hwahc_disconnect(struct usb_interface *usb_iface)
{
	struct usb_hcd *usb_hcd;
	struct wusbhc *wusbhc;
	struct hwahc *hwahc;

	usb_hcd = usb_get_intfdata(usb_iface);
	wusbhc = usb_hcd_to_wusbhc(usb_hcd);
	hwahc = container_of(wusbhc, struct hwahc, wusbhc);

	wusbhc_b_destroy(&hwahc->wusbhc);
	usb_remove_hcd(usb_hcd);
	hwahc_destroy(hwahc);
	usb_put_hcd(usb_hcd);
}
