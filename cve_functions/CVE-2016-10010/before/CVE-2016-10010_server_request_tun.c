server_request_tun(void)
{
	Channel *c = NULL;
	int mode, tun;
	int sock;

	mode = packet_get_int();
	switch (mode) {
	case SSH_TUNMODE_POINTOPOINT:
	case SSH_TUNMODE_ETHERNET:
		break;
	default:
		packet_send_debug("Unsupported tunnel device mode.");
		return NULL;
	}
	if ((options.permit_tun & mode) == 0) {
		packet_send_debug("Server has rejected tunnel device "
		    "forwarding");
		return NULL;
	}

	tun = packet_get_int();
	if (forced_tun_device != -1) {
		if (tun != SSH_TUNID_ANY && forced_tun_device != tun)
			goto done;
		tun = forced_tun_device;
	}
	sock = tun_open(tun, mode);
	if (sock < 0)
		goto done;
	c = channel_new("tun", SSH_CHANNEL_OPEN, sock, sock, -1,
	    CHAN_TCP_WINDOW_DEFAULT, CHAN_TCP_PACKET_DEFAULT, 0, "tun", 1);
	c->datagram = 1;

 done:
	if (c == NULL)
		packet_send_debug("Failed to open the tunnel device.");
	return c;
}
