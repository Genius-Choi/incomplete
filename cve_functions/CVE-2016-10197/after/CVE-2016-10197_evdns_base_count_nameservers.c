evdns_base_count_nameservers(struct evdns_base *base)
{
	const struct nameserver *server;
	int n = 0;

	EVDNS_LOCK(base);
	server = base->server_head;
	if (!server)
		goto done;
	do {
		++n;
		server = server->next;
	} while (server != base->server_head);
done:
	EVDNS_UNLOCK(base);
	return n;
}
