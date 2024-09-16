already_exist_sock(list l, sa_family_t family, int proto, ifindex_t ifindex, bool unicast)
{
	sock_t *sock;
	element e;

	LIST_FOREACH(l, sock, e) {
		if ((sock->family == family)	&&
		    (sock->proto == proto)	&&
		    (sock->ifindex == ifindex)	&&
		    (sock->unicast == unicast))
			return sock;
	}

	return NULL;
}
