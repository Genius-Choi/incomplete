rad_put_vendor_attr(struct rad_handle *h, int vendor, int type,
    const void *value, size_t len)
{
	struct vendor_attribute *attr;
	int res;
    
    if (!h->request_created) {
        generr(h, "Please call rad_create_request()");
        return -1;
    }    

	if ((attr = malloc(len + 6)) == NULL) {
		generr(h, "malloc failure (%d bytes)", len + 6);
		return -1;
	}

	attr->vendor_value = htonl(vendor);
	attr->attrib_type = type;
	attr->attrib_len = len + 2;
	memcpy(attr->attrib_data, value, len);

	res = put_raw_attr(h, RAD_VENDOR_SPECIFIC, attr, len + 6);
	free(attr);
	if (res == 0 && vendor == RAD_VENDOR_MICROSOFT
	    && (type == RAD_MICROSOFT_MS_CHAP_RESPONSE
	    || type == RAD_MICROSOFT_MS_CHAP2_RESPONSE)) {
		h->chap_pass = 1;
	}
	return (res);
}
