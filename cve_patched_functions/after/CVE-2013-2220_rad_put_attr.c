rad_put_attr(struct rad_handle *h, int type, const void *value, size_t len)
{
	int result;

    if (!h->request_created) {
        generr(h, "Please call rad_create_request()");
        return -1;
    }

	if (type == RAD_USER_PASSWORD)
		result = put_password_attr(h, type, value, len);
	else {
		result = put_raw_attr(h, type, value, len);
		if (result == 0 && type == RAD_CHAP_PASSWORD)
			h->chap_pass = 1;
	}

	return result;
}
