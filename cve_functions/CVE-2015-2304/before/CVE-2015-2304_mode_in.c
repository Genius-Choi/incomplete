mode_in(struct cpio *cpio)
{
	struct archive *a;
	struct archive_entry *entry;
	struct archive *ext;
	const char *destpath;
	int r;

	ext = archive_write_disk_new();
	if (ext == NULL)
		lafe_errc(1, 0, "Couldn't allocate restore object");
	r = archive_write_disk_set_options(ext, cpio->extract_flags);
	if (r != ARCHIVE_OK)
		lafe_errc(1, 0, "%s", archive_error_string(ext));
	a = archive_read_new();
	if (a == NULL)
		lafe_errc(1, 0, "Couldn't allocate archive object");
	archive_read_support_filter_all(a);
	archive_read_support_format_all(a);
	if (cpio->passphrase != NULL)
		r = archive_read_add_passphrase(a, cpio->passphrase);
	else
		r = archive_read_set_passphrase_callback(a, cpio,
			&passphrase_callback);
	if (r != ARCHIVE_OK)
		lafe_errc(1, 0, "%s", archive_error_string(a));

	if (archive_read_open_filename(a, cpio->filename,
					cpio->bytes_per_block))
		lafe_errc(1, archive_errno(a),
		    "%s", archive_error_string(a));
	for (;;) {
		r = archive_read_next_header(a, &entry);
		if (r == ARCHIVE_EOF)
			break;
		if (r != ARCHIVE_OK) {
			lafe_errc(1, archive_errno(a),
			    "%s", archive_error_string(a));
		}
		if (archive_match_path_excluded(cpio->matching, entry))
			continue;
		if (cpio->option_rename) {
			destpath = cpio_rename(archive_entry_pathname(entry));
			archive_entry_set_pathname(entry, destpath);
		} else
			destpath = archive_entry_pathname(entry);
		if (destpath == NULL)
			continue;
		if (cpio->verbose)
			fprintf(stderr, "%s\n", destpath);
		if (cpio->dot)
			fprintf(stderr, ".");
		if (cpio->uid_override >= 0)
			archive_entry_set_uid(entry, cpio->uid_override);
		if (cpio->gid_override >= 0)
			archive_entry_set_gid(entry, cpio->gid_override);
		r = archive_write_header(ext, entry);
		if (r != ARCHIVE_OK) {
			fprintf(stderr, "%s: %s\n",
			    archive_entry_pathname(entry),
			    archive_error_string(ext));
		} else if (!archive_entry_size_is_set(entry)
		    || archive_entry_size(entry) > 0) {
			r = extract_data(a, ext);
			if (r != ARCHIVE_OK)
				cpio->return_value = 1;
		}
	}
	r = archive_read_close(a);
	if (cpio->dot)
		fprintf(stderr, "\n");
	if (r != ARCHIVE_OK)
		lafe_errc(1, 0, "%s", archive_error_string(a));
	r = archive_write_close(ext);
	if (r != ARCHIVE_OK)
		lafe_errc(1, 0, "%s", archive_error_string(ext));
	if (!cpio->quiet) {
		int64_t blocks = (archive_filter_bytes(a, 0) + 511)
			      / 512;
		fprintf(stderr, "%lu %s\n", (unsigned long)blocks,
		    blocks == 1 ? "block" : "blocks");
	}
	archive_read_free(a);
	archive_write_free(ext);
	exit(cpio->return_value);
}
