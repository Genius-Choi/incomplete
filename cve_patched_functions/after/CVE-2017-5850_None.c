server_http_host(struct sockaddr_storage *ss, char *buf, size_t len)
{
	char		hbuf[HOST_NAME_MAX+1];
	in_port_t	port;

	if (print_host(ss, buf, len) == NULL)
		return (NULL);

	port = ntohs(server_socket_getport(ss));
	if (port == HTTP_PORT)
		return (buf);

	switch (ss->ss_family) {
	case AF_INET:
		if ((size_t)snprintf(hbuf, sizeof(hbuf),
		    "%s:%u", buf, port) >= sizeof(hbuf))
			return (NULL);
		break;
	case AF_INET6:
		if ((size_t)snprintf(hbuf, sizeof(hbuf),
		    "[%s]:%u", buf, port) >= sizeof(hbuf))
			return (NULL);
		break;
	}

	if (strlcpy(buf, hbuf, len) >= len)
		return (NULL);

	return (buf);
}
