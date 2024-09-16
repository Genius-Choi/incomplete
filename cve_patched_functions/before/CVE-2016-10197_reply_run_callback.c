reply_run_callback(struct event_callback *d, void *user_pointer)
{
	struct deferred_reply_callback *cb =
	    EVUTIL_UPCAST(d, struct deferred_reply_callback, deferred);

	switch (cb->request_type) {
	case TYPE_A:
		if (cb->have_reply)
			cb->user_callback(DNS_ERR_NONE, DNS_IPv4_A,
			    cb->reply.data.a.addrcount, cb->ttl,
			    cb->reply.data.a.addresses,
			    user_pointer);
		else
			cb->user_callback(cb->err, 0, 0, cb->ttl, NULL, user_pointer);
		break;
	case TYPE_PTR:
		if (cb->have_reply) {
			char *name = cb->reply.data.ptr.name;
			cb->user_callback(DNS_ERR_NONE, DNS_PTR, 1, cb->ttl,
			    &name, user_pointer);
		} else {
			cb->user_callback(cb->err, 0, 0, cb->ttl, NULL, user_pointer);
		}
		break;
	case TYPE_AAAA:
		if (cb->have_reply)
			cb->user_callback(DNS_ERR_NONE, DNS_IPv6_AAAA,
			    cb->reply.data.aaaa.addrcount, cb->ttl,
			    cb->reply.data.aaaa.addresses,
			    user_pointer);
		else
			cb->user_callback(cb->err, 0, 0, cb->ttl, NULL, user_pointer);
		break;
	default:
		EVUTIL_ASSERT(0);
	}

	if (cb->handle && cb->handle->pending_cb) {
		mm_free(cb->handle);
	}

	mm_free(cb);
}
