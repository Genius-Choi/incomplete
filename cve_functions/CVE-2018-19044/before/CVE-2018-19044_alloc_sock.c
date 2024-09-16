alloc_sock(sa_family_t family, list l, int proto, ifindex_t ifindex, bool unicast)
{
	sock_t *new;

	new = (sock_t *)MALLOC(sizeof (sock_t));
	new->family = family;
	new->proto = proto;
	new->ifindex = ifindex;
	new->unicast = unicast;
	new->rb_vrid = RB_ROOT;
	new->rb_sands = RB_ROOT_CACHED;

	list_add(l, new);

	return new;
}
