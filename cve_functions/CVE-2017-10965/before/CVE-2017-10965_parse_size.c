int parse_size(const char *size, int *bytes)
{
	guint bytes_;
	int ret;

	ret = parse_size_uint(size, &bytes_);

	if (bytes_ > (1U << 31)) {
		return FALSE;
	}

	*bytes = bytes_;
	return ret;
}
