static void dwc3_gadget_start_isoc(struct dwc3 *dwc,
		struct dwc3_ep *dep, const struct dwc3_event_depevt *event)
{
	u32 cur_uf, mask;

	mask = ~(dep->interval - 1);
	cur_uf = event->parameters & mask;

	__dwc3_gadget_start_isoc(dwc, dep, cur_uf);
}
