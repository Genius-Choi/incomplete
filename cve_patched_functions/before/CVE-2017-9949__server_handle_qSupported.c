static int _server_handle_qSupported(libgdbr_t *g) {
	int ret;
	char *buf;
	if (!(buf = malloc (128))) {
		return -1;
	}
	snprintf (buf, 127, "PacketSize=%x", (ut32) (g->read_max - 1));
	if ((ret = handle_qSupported (g)) < 0) {
		return -1;
	}
	ret = send_msg (g, buf);
	free (buf);
	return ret;
}
