static bool login_as_unix_peer(PgSocket *client)
{
	if (!pga_is_unix(&client->remote_addr))
		goto fail;
	if (!check_unix_peer_name(sbuf_socket(&client->sbuf), client->auth_user->name))
		goto fail;
	return finish_client_login(client);
fail:
	disconnect_client(client, true, "unix socket login rejected");
	return false;
}
