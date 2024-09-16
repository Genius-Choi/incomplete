rad_put_string(struct rad_handle *h, int type, const char *str)
{
	return rad_put_attr(h, type, str, strlen(str));
}
