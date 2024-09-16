static int dwc3_gadget_get_frame(struct usb_gadget *g)
{
	struct dwc3		*dwc = gadget_to_dwc(g);

	return __dwc3_gadget_get_frame(dwc);
}
