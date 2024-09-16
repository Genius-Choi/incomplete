static void dwc3_gadget_suspend_interrupt(struct dwc3 *dwc,
					  unsigned int evtinfo)
{
	enum dwc3_link_state next = evtinfo & DWC3_LINK_STATE_MASK;

	if (dwc->link_state != next && next == DWC3_LINK_STATE_U3)
		dwc3_suspend_gadget(dwc);

	dwc->link_state = next;
}
