evdns_base_nameserver_sockaddr_add(struct evdns_base *base,
    const struct sockaddr *sa, ev_socklen_t len, unsigned flags)
{
	int res;
	EVUTIL_ASSERT(base);
	EVDNS_LOCK(base);
	res = evdns_nameserver_add_impl_(base, sa, len);
	EVDNS_UNLOCK(base);
	return res;
}
