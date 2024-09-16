close_all_listening_sockets(struct mg_context *ctx)
{
	unsigned int i;
	if (!ctx) {
		return;
	}

	for (i = 0; i < ctx->num_listening_sockets; i++) {
		closesocket(ctx->listening_sockets[i].sock);
		ctx->listening_sockets[i].sock = INVALID_SOCKET;
	}
	mg_free(ctx->listening_sockets);
	ctx->listening_sockets = NULL;
	mg_free(ctx->listening_socket_fds);
	ctx->listening_socket_fds = NULL;
}
