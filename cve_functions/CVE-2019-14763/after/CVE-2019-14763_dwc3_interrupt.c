static irqreturn_t dwc3_interrupt(int irq, void *_evt)
{
	struct dwc3_event_buffer	*evt = _evt;

	return dwc3_check_event_buf(evt);
}
