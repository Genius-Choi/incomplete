authentic_parse_size(unsigned char *in, size_t *out)
{
	if (!in || !out)
		return SC_ERROR_INVALID_ARGUMENTS;

	if (*in < 0x80)   {
		*out = *in;
		return 1;
	}
	else if (*in == 0x81)   {
		*out = *(in + 1);
		return 2;
	}
	else if (*in == 0x82)   {
		*out = *(in + 1) * 0x100 + *(in + 2);
		return 3;
	}

	return SC_ERROR_INVALID_DATA;
}
