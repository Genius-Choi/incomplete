rad_put_addr(struct rad_handle *h, int type, struct in_addr addr)
{
	return rad_put_attr(h, type, &addr.s_addr, sizeof addr.s_addr);
}
