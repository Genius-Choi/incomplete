evutil_getaddrinfo_async_(struct evdns_base *dns_base,
    const char *nodename, const char *servname,
    const struct evutil_addrinfo *hints_in,
    void (*cb)(int, struct evutil_addrinfo *, void *), void *arg)
{
	if (dns_base && evdns_getaddrinfo_impl) {
		evdns_getaddrinfo_impl(
			dns_base, nodename, servname, hints_in, cb, arg);
	} else {
		struct evutil_addrinfo *ai=NULL;
		int err;
		err = evutil_getaddrinfo(nodename, servname, hints_in, &ai);
		cb(err, ai, arg);
	}
	return 0;
}
