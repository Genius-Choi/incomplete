evdns_resolv_conf_parse(int flags, const char *const filename) {
	if (!current_base)
		current_base = evdns_base_new(NULL, 0);
	return evdns_base_resolv_conf_parse(current_base, flags, filename);
}
