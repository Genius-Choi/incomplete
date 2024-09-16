rad_get_attr(struct rad_handle *h, const void **value, size_t *len)
{
	int type;

	if (h->resp_pos >= h->resp_len)
		return 0;
	if (h->resp_pos + 2 > h->resp_len) {
		generr(h, "Malformed attribute in response");
		return -1;
	}
	type = h->response[h->resp_pos++];
	*len = h->response[h->resp_pos++] - 2;
	if (h->resp_pos + (int) *len > h->resp_len) {
		generr(h, "Malformed attribute in response");
		return -1;
	}
	*value = &h->response[h->resp_pos];
	h->resp_pos += *len;
	return type;
}
