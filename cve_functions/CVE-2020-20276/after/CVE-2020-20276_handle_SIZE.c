static void handle_SIZE(ctrl_t *ctrl, char *file)
{
	char *path;
	char buf[80];
	size_t extralen = 0;
	struct stat st;

	path = compose_abspath(ctrl, file);
	if (!path || stat(path, &st) || S_ISDIR(st.st_mode)) {
		send_msg(ctrl->sd, "550 No such file, or argument is a directory.\r\n");
		return;
	}

	DBG("SIZE %s", path);

	if (ctrl->type == TYPE_A)
		extralen = num_nl(path);

	snprintf(buf, sizeof(buf), "213 %"  PRIu64 "\r\n", (uint64_t)(st.st_size + extralen));
	send_msg(ctrl->sd, buf);
}
