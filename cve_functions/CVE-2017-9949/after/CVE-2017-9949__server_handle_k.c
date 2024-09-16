static int _server_handle_k(libgdbr_t *g, int (*cmd_cb) (void*, const char*, char*, size_t), void *core_ptr) {
	send_ack (g);
	return -1;
}
