nameserver_probe_failed(struct nameserver *const ns) {
	struct timeval timeout;
	int i;

	ASSERT_LOCKED(ns->base);
	(void) evtimer_del(&ns->timeout_event);
	if (ns->state == 1) {
		/* This can happen if the nameserver acts in a way which makes us mark */
		/* it as bad and then starts sending good replies. */
		return;
	}

#define MAX_PROBE_TIMEOUT 3600
#define TIMEOUT_BACKOFF_FACTOR 3

	memcpy(&timeout, &ns->base->global_nameserver_probe_initial_timeout,
	    sizeof(struct timeval));
	for (i=ns->failed_times; i > 0 && timeout.tv_sec < MAX_PROBE_TIMEOUT; --i) {
		timeout.tv_sec *= TIMEOUT_BACKOFF_FACTOR;
		timeout.tv_usec *= TIMEOUT_BACKOFF_FACTOR;
		if (timeout.tv_usec > 1000000) {
			timeout.tv_sec += timeout.tv_usec / 1000000;
			timeout.tv_usec %= 1000000;
		}
	}
	if (timeout.tv_sec > MAX_PROBE_TIMEOUT) {
		timeout.tv_sec = MAX_PROBE_TIMEOUT;
		timeout.tv_usec = 0;
	}

	ns->failed_times++;

	if (evtimer_add(&ns->timeout_event, &timeout) < 0) {
		char addrbuf[128];
		log(EVDNS_LOG_WARN,
		    "Error from libevent when adding timer event for %s",
		    evutil_format_sockaddr_port_(
			    (struct sockaddr *)&ns->address,
			    addrbuf, sizeof(addrbuf)));
	}
}
