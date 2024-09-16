static int asn1_write_element(sc_context_t *ctx, unsigned int tag,
	const u8 * data, size_t datalen, u8 ** out, size_t * outlen)
{
	unsigned char t;
	unsigned char *buf, *p;
	int c = 0;
	unsigned short_tag;
	unsigned char tag_char[3] = {0, 0, 0};
	size_t tag_len, ii;

	short_tag = tag & SC_ASN1_TAG_MASK;
	for (tag_len = 0; short_tag >> (8 * tag_len); tag_len++)
		tag_char[tag_len] = (short_tag >> (8 * tag_len)) & 0xFF;
	if (!tag_len)
		tag_len = 1;

	if (tag_len > 1)   {
		if ((tag_char[tag_len - 1] & SC_ASN1_TAG_PRIMITIVE) != SC_ASN1_TAG_ESCAPE_MARKER)
			SC_TEST_RET(ctx, SC_LOG_DEBUG_ASN1, SC_ERROR_INVALID_DATA, "First byte of the long tag is not 'escape marker'");

		for (ii = 1; ii < tag_len - 1; ii++)
			if (!(tag_char[ii] & 0x80))
				SC_TEST_RET(ctx, SC_LOG_DEBUG_ASN1, SC_ERROR_INVALID_DATA, "MS bit expected to be 'one'");

		if (tag_char[0] & 0x80)
			SC_TEST_RET(ctx, SC_LOG_DEBUG_ASN1, SC_ERROR_INVALID_DATA, "MS bit of the last byte expected to be 'zero'");
	}

	t = tag_char[tag_len - 1] & 0x1F;

	switch (tag & SC_ASN1_CLASS_MASK) {
	case SC_ASN1_UNI:
		break;
	case SC_ASN1_APP:
		t |= SC_ASN1_TAG_APPLICATION;
		break;
	case SC_ASN1_CTX:
		t |= SC_ASN1_TAG_CONTEXT;
		break;
	case SC_ASN1_PRV:
		t |= SC_ASN1_TAG_PRIVATE;
		break;
	}
	if (tag & SC_ASN1_CONS)
		t |= SC_ASN1_TAG_CONSTRUCTED;
	if (datalen > 127) {
		c = 1;
		while (datalen >> (c << 3))
			c++;
	}

	*outlen = tag_len + 1 + c + datalen;
	buf = malloc(*outlen);
	if (buf == NULL)
		SC_FUNC_RETURN(ctx, SC_LOG_DEBUG_ASN1, SC_ERROR_OUT_OF_MEMORY);

	*out = p = buf;
	*p++ = t;
	for (ii=1;ii<tag_len;ii++)
		*p++ = tag_char[tag_len - ii - 1];

	if (c) {
		*p++ = 0x80 | c;
		while (c--)
			*p++ = (datalen >> (c << 3)) & 0xFF;
	}
	else   {
		*p++ = datalen & 0x7F;
	}
	memcpy(p, data, datalen);

	return SC_SUCCESS;
}
