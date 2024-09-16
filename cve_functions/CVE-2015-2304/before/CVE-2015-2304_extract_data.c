extract_data(struct archive *ar, struct archive *aw)
{
	int r;
	size_t size;
	const void *block;
	int64_t offset;

	for (;;) {
		r = archive_read_data_block(ar, &block, &size, &offset);
		if (r == ARCHIVE_EOF)
			return (ARCHIVE_OK);
		if (r != ARCHIVE_OK) {
			lafe_warnc(archive_errno(ar),
			    "%s", archive_error_string(ar));
			exit(1);
		}
		r = (int)archive_write_data_block(aw, block, size, offset);
		if (r != ARCHIVE_OK) {
			lafe_warnc(archive_errno(aw),
			    "%s", archive_error_string(aw));
			return (r);
		}
	}
}
