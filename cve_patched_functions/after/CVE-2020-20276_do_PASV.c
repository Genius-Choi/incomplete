static int do_PASV(ctrl_t *ctrl, char *arg, struct sockaddr *data, socklen_t *len)
{
	struct sockaddr_in server;

	if (ctrl->data_sd > 0) {
		close(ctrl->data_sd);
		ctrl->data_sd = -1;
	}

	if (ctrl->data_listen_sd > 0)
		close(ctrl->data_listen_sd);

	ctrl->data_listen_sd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (ctrl->data_listen_sd < 0) {
		ERR(errno, "Failed opening data server socket");
		send_msg(ctrl->sd, "426 Internal server error.\r\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_family      = AF_INET;
	server.sin_addr.s_addr = inet_addr(ctrl->serveraddr);
	server.sin_port        = htons(0);
	if (bind(ctrl->data_listen_sd, (struct sockaddr *)&server, sizeof(server)) < 0) {
		ERR(errno, "Failed binding to client socket");
		send_msg(ctrl->sd, "426 Internal server error.\r\n");
		close(ctrl->data_listen_sd);
		ctrl->data_listen_sd = -1;
		return 1;
	}

	INFO("Data server port estabished.  Waiting for client to connect ...");
	if (listen(ctrl->data_listen_sd, 1) < 0) {
		ERR(errno, "Client data connection failure");
		send_msg(ctrl->sd, "426 Internal server error.\r\n");
		close(ctrl->data_listen_sd);
		ctrl->data_listen_sd = -1;
		return 1;
	}

	memset(data, 0, sizeof(*data));
	if (-1 == getsockname(ctrl->data_listen_sd, data, len)) {
		ERR(errno, "Cannot determine our address, need it if client should connect to us");
		close(ctrl->data_listen_sd);
		ctrl->data_listen_sd = -1;
		return 1;
	}

	uev_io_init(ctrl->ctx, &ctrl->data_watcher, do_pasv_connection, ctrl, ctrl->data_listen_sd, UEV_READ);

	return 0;
}
