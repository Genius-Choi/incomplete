static int _server_handle_m(libgdbr_t *g, int (*cmd_cb) (void*, const char*, char*, size_t), void *core_ptr) {
	int ret;
	ut64 addr;
	int length;
	char *buf1, *buf2, cmd[64];
	int buf1_len, buf2_len;

	if (send_ack (g) < 0) {
		return -1;
	}
	g->data[g->data_len] = 0;
	sscanf (g->data, "m%"PFMT64x",%d", &addr, &length);
	if (g->data_len < 4 || !strchr (g->data, ',')) {
		return send_msg (g, "E01");
	}
	buf1_len = length;
	buf2_len = length * 2 + 1;
	if (!(buf1 = malloc (buf1_len))) {
		return -1;
	}
	if (!(buf2 = malloc (buf2_len))) {
		free (buf1);
		return -1;
	}
	memset (buf2, 0, buf2_len);
	snprintf (cmd, sizeof (cmd) - 1, "m %"PFMT64x" %d", addr, length);
	if ((buf1_len = cmd_cb (core_ptr, cmd, buf1, buf1_len)) < 0) {
		free (buf1);
		free (buf2);
		send_msg (g, "E01");
		return -1;
	}
	pack_hex (buf1, buf1_len, buf2);
	ret = send_msg (g, buf2);
	free (buf1);
	free (buf2);
	return ret;
}
