static void connect_reply_upcall(struct iwch_ep *ep, int status)
{
	struct iw_cm_event event;

	PDBG("%s ep %p status %d\n", __func__, ep, status);
	memset(&event, 0, sizeof(event));
	event.event = IW_CM_EVENT_CONNECT_REPLY;
	event.status = status;
	memcpy(&event.local_addr, &ep->com.local_addr,
	       sizeof(ep->com.local_addr));
	memcpy(&event.remote_addr, &ep->com.remote_addr,
	       sizeof(ep->com.remote_addr));

	if ((status == 0) || (status == -ECONNREFUSED)) {
		event.private_data_len = ep->plen;
		event.private_data = ep->mpa_pkt + sizeof(struct mpa_message);
	}
	if (ep->com.cm_id) {
		PDBG("%s ep %p tid %d status %d\n", __func__, ep,
		     ep->hwtid, status);
		ep->com.cm_id->event_handler(ep->com.cm_id, &event);
	}
	if (status < 0) {
		ep->com.cm_id->rem_ref(ep->com.cm_id);
		ep->com.cm_id = NULL;
		ep->com.qp = NULL;
	}
}
