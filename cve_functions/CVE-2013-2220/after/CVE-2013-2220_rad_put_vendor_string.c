rad_put_vendor_string(struct rad_handle *h, int vendor, int type,
    const char *str)
{
	return (rad_put_vendor_attr(h, vendor, type, str, strlen(str)));
}
