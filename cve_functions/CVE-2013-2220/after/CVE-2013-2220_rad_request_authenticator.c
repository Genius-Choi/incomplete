rad_request_authenticator(struct rad_handle *h, char *buf, size_t len)
{
	if (len < LEN_AUTH)
		return (-1);
	memcpy(buf, h->request + POS_AUTH, LEN_AUTH);
	if (len > LEN_AUTH)
		buf[LEN_AUTH] = '\0';
	return (LEN_AUTH);
}
