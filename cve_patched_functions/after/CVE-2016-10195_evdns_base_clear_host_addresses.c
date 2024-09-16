evdns_base_clear_host_addresses(struct evdns_base *base)
{
	struct hosts_entry *victim;
	EVDNS_LOCK(base);
	while ((victim = TAILQ_FIRST(&base->hostsdb))) {
		TAILQ_REMOVE(&base->hostsdb, victim, next);
		mm_free(victim);
	}
	EVDNS_UNLOCK(base);
}
