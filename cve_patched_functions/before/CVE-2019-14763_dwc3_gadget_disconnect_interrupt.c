static void dwc3_gadget_disconnect_interrupt(struct dwc3 *dwc)
{
	int			reg;

	reg = dwc3_readl(dwc->regs, DWC3_DCTL);
	reg &= ~DWC3_DCTL_INITU1ENA;
	dwc3_writel(dwc->regs, DWC3_DCTL, reg);

	reg &= ~DWC3_DCTL_INITU2ENA;
	dwc3_writel(dwc->regs, DWC3_DCTL, reg);

	dwc3_disconnect_gadget(dwc);

	dwc->gadget.speed = USB_SPEED_UNKNOWN;
	dwc->setup_packet_pending = false;
	usb_gadget_set_state(&dwc->gadget, USB_STATE_NOTATTACHED);

	dwc->connected = false;
}
