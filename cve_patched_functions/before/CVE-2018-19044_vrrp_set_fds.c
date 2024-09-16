vrrp_set_fds(list l)
{
	sock_t *sock;
	vrrp_t *vrrp;
	element e;

	LIST_FOREACH(l, sock, e) {
		rb_for_each_entry(vrrp, &sock->rb_vrid, rb_vrid)
			vrrp->sockets = sock;
	}
}
