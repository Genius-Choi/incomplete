__archive_write_nulls(struct archive_write *a, size_t length)
{
	if (length == 0)
		return (ARCHIVE_OK);

	while (length > 0) {
		size_t to_write = length < a->null_length ? length : a->null_length;
		int r = __archive_write_output(a, a->nulls, to_write);
		if (r < ARCHIVE_OK)
			return (r);
		length -= to_write;
	}
	return (ARCHIVE_OK);
}
