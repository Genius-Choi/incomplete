int ftp_session(uev_ctx_t *ctx, int sd)
{
	int pid = 0;
	ctrl_t *ctrl;
	socklen_t len;

	ctrl = new_session(ctx, sd, &pid);
	if (!ctrl) {
		if (pid < 0) {
			shutdown(sd, SHUT_RDWR);
			close(sd);
		}

		return pid;
	}

	len = sizeof(ctrl->server_sa);
	if (-1 == getsockname(sd, (struct sockaddr *)&ctrl->server_sa, &len)) {
		ERR(errno, "Cannot determine our address");
		goto fail;
	}
	convert_address(&ctrl->server_sa, ctrl->serveraddr, sizeof(ctrl->serveraddr));

	len = sizeof(ctrl->client_sa);
	if (-1 == getpeername(sd, (struct sockaddr *)&ctrl->client_sa, &len)) {
		ERR(errno, "Cannot determine client address");
		goto fail;
	}
	convert_address(&ctrl->client_sa, ctrl->clientaddr, sizeof(ctrl->clientaddr));

	ctrl->type = TYPE_A;
	ctrl->data_listen_sd = -1;
	ctrl->data_sd = -1;
	ctrl->name[0] = 0;
	ctrl->pass[0] = 0;
	ctrl->data_address[0] = 0;
	strlcpy(ctrl->facts, "mpst", sizeof(ctrl->facts));

	INFO("Client connection from %s", ctrl->clientaddr);
	ftp_command(ctrl);

	DBG("Client exiting, bye");
	exit(del_session(ctrl, 1));
fail:
	free(ctrl);
	shutdown(sd, SHUT_RDWR);
	close(sd);

	return -1;
}
