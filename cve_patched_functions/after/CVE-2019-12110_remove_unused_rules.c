remove_unused_rules(struct rule_state * list)
{
	char ifname[IFNAMSIZ];
	unsigned short iport;
	struct rule_state * tmp;
	u_int64_t packets;
	u_int64_t bytes;
	unsigned int timestamp;
	int n = 0;

	while(list)
	{
		/* remove the rule if no traffic has used it */
		if(get_redirect_rule(ifname, list->eport, list->proto,
	                         0, 0, &iport, 0, 0, 0, 0, &timestamp,
		                     &packets, &bytes) >= 0)
		{
			if(packets == list->packets && bytes == list->bytes)
			{
				syslog(LOG_DEBUG, "removing unused mapping %hu %s : still "
				       "%" PRIu64 "packets %" PRIu64 "bytes",
				       list->eport, proto_itoa(list->proto),
				       packets, bytes);
				_upnp_delete_redir(list->eport, list->proto);
				n++;
			}
		}
		tmp = list;
		list = tmp->next;
		free(tmp);
	}
	if(n>0)
		syslog(LOG_NOTICE, "removed %d unused rules", n);
}
