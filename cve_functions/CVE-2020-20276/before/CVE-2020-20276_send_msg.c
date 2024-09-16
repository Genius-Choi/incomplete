static int send_msg(int sd, char *msg)
{
	int n = 0;
	int l;

	if (!msg) {
	err:
		ERR(EINVAL, "Missing argument to send_msg()");
		return 1;
	}

	l = strlen(msg);
	if (l <= 0)
		goto err;

	while (n < l) {
		int result = send(sd, msg + n, l, 0);

		if (result < 0) {
			ERR(errno, "Failed sending message to client");
			return 1;
		}

		n += result;
	}

	DBG("Sent: %s%s", is_cont(msg) ? "\n" : "", msg);

	return 0;
}
