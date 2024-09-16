evdns_transmit(struct evdns_base *base) {
	char did_try_to_transmit = 0;
	int i;

	ASSERT_LOCKED(base);
	for (i = 0; i < base->n_req_heads; ++i) {
		if (base->req_heads[i]) {
			struct request *const started_at = base->req_heads[i], *req = started_at;
			/* first transmit all the requests which are currently waiting */
			do {
				if (req->transmit_me) {
					did_try_to_transmit = 1;
					evdns_request_transmit(req);
				}

				req = req->next;
			} while (req != started_at);
		}
	}

	return did_try_to_transmit;
}
