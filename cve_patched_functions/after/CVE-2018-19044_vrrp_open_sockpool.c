vrrp_open_sockpool(list l)
{
	sock_t *sock;
	element e;
	interface_t *ifp;

	LIST_FOREACH(l, sock, e) {
		if (!sock->ifindex) {
			sock->fd_in = sock->fd_out = -1;
			continue;
		}
		ifp = if_get_by_ifindex(sock->ifindex);
		sock->fd_in = open_vrrp_read_socket(sock->family, sock->proto,
					       ifp, sock->unicast, sock->rx_buf_size);
		if (sock->fd_in == -1)
			sock->fd_out = -1;
		else
			sock->fd_out = open_vrrp_send_socket(sock->family, sock->proto,
							     ifp, sock->unicast);
	}
}
