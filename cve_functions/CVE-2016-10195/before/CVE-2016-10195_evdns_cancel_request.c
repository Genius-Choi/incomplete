evdns_cancel_request(struct evdns_base *base, struct evdns_request *handle)
{
	struct request *req;

	if (!handle->current_req)
		return;

	if (!base) {
		/* This redundancy is silly; can we fix it? (Not for 2.0) XXXX */
		base = handle->base;
		if (!base)
			base = handle->current_req->base;
	}

	EVDNS_LOCK(base);
	if (handle->pending_cb) {
		EVDNS_UNLOCK(base);
		return;
	}

	req = handle->current_req;
	ASSERT_VALID_REQUEST(req);

	reply_schedule_callback(req, 0, DNS_ERR_CANCEL, NULL);
	if (req->ns) {
		/* remove from inflight queue */
		request_finished(req, &REQ_HEAD(base, req->trans_id), 1);
	} else {
		/* remove from global_waiting head */
		request_finished(req, &base->req_waiting_head, 1);
	}
	EVDNS_UNLOCK(base);
}
