void server_ref(SERVER_REC *server)
{
	g_return_if_fail(IS_SERVER(server));

	server->refcount++;
}
