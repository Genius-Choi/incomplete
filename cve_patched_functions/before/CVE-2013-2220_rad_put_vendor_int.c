rad_put_vendor_int(struct rad_handle *h, int vendor, int type, u_int32_t i)
{
	u_int32_t value;

	value = htonl(i);
	return (rad_put_vendor_attr(h, vendor, type, &value, sizeof value));
}
