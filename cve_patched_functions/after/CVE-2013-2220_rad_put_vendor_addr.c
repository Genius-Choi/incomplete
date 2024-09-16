rad_put_vendor_addr(struct rad_handle *h, int vendor, int type,
    struct in_addr addr)
{
	return (rad_put_vendor_attr(h, vendor, type, &addr.s_addr,
	    sizeof addr.s_addr));
}
