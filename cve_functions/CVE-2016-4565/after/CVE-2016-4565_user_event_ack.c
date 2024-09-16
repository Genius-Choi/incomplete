static int user_event_ack(struct hfi1_ctxtdata *uctxt, int subctxt,
			  unsigned long events)
{
	int i;
	struct hfi1_devdata *dd = uctxt->dd;
	unsigned long *evs;

	if (!dd->events)
		return 0;

	evs = dd->events + ((uctxt->ctxt - dd->first_user_ctxt) *
			    HFI1_MAX_SHARED_CTXTS) + subctxt;

	for (i = 0; i <= _HFI1_MAX_EVENT_BIT; i++) {
		if (!test_bit(i, &events))
			continue;
		clear_bit(i, evs);
	}
	return 0;
}
