int sctp_for_each_transport(int (*cb)(struct sctp_transport *, void *),
			    struct net *net, int pos, void *p) {
	struct rhashtable_iter hti;
	void *obj;
	int err;

	err = sctp_transport_walk_start(&hti);
	if (err)
		return err;

	sctp_transport_get_idx(net, &hti, pos);
	obj = sctp_transport_get_next(net, &hti);
	for (; obj && !IS_ERR(obj); obj = sctp_transport_get_next(net, &hti)) {
		struct sctp_transport *transport = obj;

		if (!sctp_transport_hold(transport))
			continue;
		err = cb(transport, p);
		sctp_transport_put(transport);
		if (err)
			break;
	}
	sctp_transport_walk_stop(&hti);

	return err;
}
