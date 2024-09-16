int server_unref(SERVER_REC *server)
{
	g_return_val_if_fail(IS_SERVER(server), FALSE);

	if (--server->refcount > 0)
		return TRUE;

	if (g_slist_find(servers, server) != NULL) {
		g_warning("Non-referenced server wasn't disconnected");
		server_disconnect(server);
		return TRUE;
	}

        MODULE_DATA_DEINIT(server);
	server_connect_unref(server->connrec);
	if (server->rawlog != NULL) rawlog_destroy(server->rawlog);
	g_free(server->version);
	g_free(server->away_reason);
	g_free(server->nick);
	g_free(server->tag);

	server->type = 0;
	g_free(server);
        return FALSE;
}
