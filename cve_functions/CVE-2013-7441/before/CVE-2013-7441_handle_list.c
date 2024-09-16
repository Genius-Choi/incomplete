static void handle_list(uint32_t opt, int net, GArray* servers, uint32_t cflags) {
	uint32_t len;
	int i;
	char buf[1024];
	char *ptr = buf + sizeof(len);

	if (read(net, &len, sizeof(len)) < 0)
		err("Negotiation failed/8: %m");
	len = ntohl(len);
	if(len) {
		send_reply(opt, net, NBD_REP_ERR_INVALID, 0, NULL);
	}
	if(!(glob_flags & F_LIST)) {
		send_reply(opt, net, NBD_REP_ERR_POLICY, 0, NULL);
		err_nonfatal("Client tried disallowed list option");
		return;
	}
	for(i=0; i<servers->len; i++) {
		SERVER* serve = &(g_array_index(servers, SERVER, i));
		len = htonl(strlen(serve->servename));
		memcpy(buf, &len, sizeof(len));
		strcpy(ptr, serve->servename);
		send_reply(opt, net, NBD_REP_SERVER, strlen(serve->servename)+sizeof(len), buf);
	}
	send_reply(opt, net, NBD_REP_ACK, 0, NULL);
}
