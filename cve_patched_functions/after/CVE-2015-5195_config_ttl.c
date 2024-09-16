config_ttl(
	config_tree *ptree
	)
{
	int i = 0;
	int_node *curr_ttl;

	curr_ttl = HEAD_PFIFO(ptree->ttl);
	for (; curr_ttl != NULL; curr_ttl = curr_ttl->link) {
		if (i < COUNTOF(sys_ttl))
			sys_ttl[i++] = (u_char)curr_ttl->i;
		else
			msyslog(LOG_INFO,
				"ttl: Number of TTL entries exceeds %lu. Ignoring TTL %d...",
				(u_long)COUNTOF(sys_ttl), curr_ttl->i);
	}
	sys_ttlmax = i - 1;
}
