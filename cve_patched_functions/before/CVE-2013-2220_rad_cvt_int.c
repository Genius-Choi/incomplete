rad_cvt_int(const void *data)
{
	u_int32_t value;

	memcpy(&value, data, sizeof value);
	return ntohl(value);
}
