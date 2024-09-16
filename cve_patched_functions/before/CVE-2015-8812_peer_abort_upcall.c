static void peer_abort_upcall(struct iwch_ep *ep)
{
	struct iw_cm_event event;

	PDBG("%s ep %p\n", __func__, ep);
	memset(&event, 0, sizeof(event));
	event.event = IW_CM_EVENT_CLOSE;
	event.status = -ECONNRESET;
	if (ep->com.cm_id) {
		PDBG("abort delivered ep %p cm_id %p tid %d\n", ep,
		     ep->com.cm_id, ep->hwtid);
		ep->com.cm_id->event_handler(ep->com.cm_id, &event);
		ep->com.cm_id->rem_ref(ep->com.cm_id);
		ep->com.cm_id = NULL;
		ep->com.qp = NULL;
	}
}
