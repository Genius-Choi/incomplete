put_raw_attr(struct rad_handle *h, int type, const void *value, size_t len)
{
	if (len > 253) {
		generr(h, "Attribute too long");
		return -1;
	}
	
	if (h->req_len + 2 + len > MSGSIZE) {
		generr(h, "Maximum message length exceeded");
		return -1;
	}
	h->request[h->req_len++] = type;
	h->request[h->req_len++] = len + 2;
	memcpy(&h->request[h->req_len], value, len);
	h->req_len += len;
	return 0;
}
