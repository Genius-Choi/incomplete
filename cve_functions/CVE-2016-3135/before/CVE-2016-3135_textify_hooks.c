textify_hooks(char *buf, size_t size, unsigned int mask, uint8_t nfproto)
{
	static const char *const inetbr_names[] = {
		"PREROUTING", "INPUT", "FORWARD",
		"OUTPUT", "POSTROUTING", "BROUTING",
	};
	static const char *const arp_names[] = {
		"INPUT", "FORWARD", "OUTPUT",
	};
	const char *const *names;
	unsigned int i, max;
	char *p = buf;
	bool np = false;
	int res;

	names = (nfproto == NFPROTO_ARP) ? arp_names : inetbr_names;
	max   = (nfproto == NFPROTO_ARP) ? ARRAY_SIZE(arp_names) :
	                                   ARRAY_SIZE(inetbr_names);
	*p = '\0';
	for (i = 0; i < max; ++i) {
		if (!(mask & (1 << i)))
			continue;
		res = snprintf(p, size, "%s%s", np ? "/" : "", names[i]);
		if (res > 0) {
			size -= res;
			p += res;
		}
		np = true;
	}

	return buf;
}
