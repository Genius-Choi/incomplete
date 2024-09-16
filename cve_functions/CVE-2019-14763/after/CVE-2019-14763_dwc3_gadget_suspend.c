int dwc3_gadget_suspend(struct dwc3 *dwc)
{
	if (!dwc->gadget_driver)
		return 0;

	dwc3_gadget_run_stop(dwc, false, false);
	dwc3_disconnect_gadget(dwc);
	__dwc3_gadget_stop(dwc);

	return 0;
}
