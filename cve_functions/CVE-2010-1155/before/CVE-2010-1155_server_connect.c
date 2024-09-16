SERVER_REC *server_connect(SERVER_CONNECT_REC *conn)
{
	CHAT_PROTOCOL_REC *proto;
	SERVER_REC *server;

	proto = CHAT_PROTOCOL(conn);
	server = proto->server_init_connect(conn);
	proto->server_connect(server);

	return server;
}
