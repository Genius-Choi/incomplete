SERVER* dup_serve(const SERVER *const s) {
	SERVER *serve = NULL;

	serve=g_new0(SERVER, 1);
	if(serve == NULL)
		return NULL;

	if(s->exportname)
		serve->exportname = g_strdup(s->exportname);

	serve->expected_size = s->expected_size;

	if(s->listenaddr)
		serve->listenaddr = g_strdup(s->listenaddr);

	serve->port = s->port;

	if(s->authname)
		serve->authname = strdup(s->authname);

	serve->flags = s->flags;
	serve->socket = s->socket;
	serve->socket_family = s->socket_family;
	serve->virtstyle = s->virtstyle;
	serve->cidrlen = s->cidrlen;

	if(s->prerun)
		serve->prerun = g_strdup(s->prerun);

	if(s->postrun)
		serve->postrun = g_strdup(s->postrun);

	if(s->transactionlog)
		serve->transactionlog = g_strdup(s->transactionlog);
	
	if(s->servename)
		serve->servename = g_strdup(s->servename);

	serve->max_connections = s->max_connections;

	return serve;
}
