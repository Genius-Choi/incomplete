void dwc3_gadget_exit(struct dwc3 *dwc)
{
	usb_del_gadget_udc(&dwc->gadget);
	dwc3_gadget_free_endpoints(dwc);
	dma_free_coherent(dwc->sysdev, DWC3_BOUNCE_SIZE, dwc->bounce,
			  dwc->bounce_addr);
	kfree(dwc->setup_buf);
	dma_free_coherent(dwc->sysdev, sizeof(*dwc->ep0_trb) * 2,
			  dwc->ep0_trb, dwc->ep0_trb_addr);
}
