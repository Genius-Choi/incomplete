static int qib_user_event_ack(struct qib_ctxtdata *rcd, int subctxt,
			      unsigned long events)
{
	int ret = 0, i;

	for (i = 0; i <= _QIB_MAX_EVENT_BIT; i++) {
		if (!test_bit(i, &events))
			continue;
		if (i == _QIB_EVENT_DISARM_BUFS_BIT) {
			(void)qib_disarm_piobufs_ifneeded(rcd);
			ret = disarm_req_delay(rcd);
		} else
			clear_bit(i, &rcd->user_event_mask[subctxt]);
	}
	return ret;
}
