xar_read_header(struct archive_read *a, struct archive_entry *entry)
{
	struct xar *xar;
	struct xar_file *file;
	struct xattr *xattr;
	int r;

	xar = (struct xar *)(a->format->data);
	r = ARCHIVE_OK;

	if (xar->offset == 0) {
		/* Create a character conversion object. */
		if (xar->sconv == NULL) {
			xar->sconv = archive_string_conversion_from_charset(
			    &(a->archive), "UTF-8", 1);
			if (xar->sconv == NULL)
				return (ARCHIVE_FATAL);
		}

		/* Read TOC. */
		r = read_toc(a);
		if (r != ARCHIVE_OK)
			return (r);
	}

	for (;;) {
		file = xar->file = heap_get_entry(&(xar->file_queue));
		if (file == NULL) {
			xar->end_of_file = 1;
			return (ARCHIVE_EOF);
		}
		if ((file->mode & AE_IFMT) != AE_IFDIR)
			break;
		if (file->has != (HAS_PATHNAME | HAS_TYPE))
			break;
		/*
		 * If a file type is a directory and it does not have
		 * any metadata, do not export.
		 */
		file_free(file);
	}
	archive_entry_set_atime(entry, file->atime, 0);
	archive_entry_set_ctime(entry, file->ctime, 0);
	archive_entry_set_mtime(entry, file->mtime, 0);
	archive_entry_set_gid(entry, file->gid);
	if (file->gname.length > 0 &&
	    archive_entry_copy_gname_l(entry, file->gname.s,
		archive_strlen(&(file->gname)), xar->sconv) != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Gname");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Gname cannot be converted from %s to current locale.",
		    archive_string_conversion_charset_name(xar->sconv));
		r = ARCHIVE_WARN;
	}
	archive_entry_set_uid(entry, file->uid);
	if (file->uname.length > 0 &&
	    archive_entry_copy_uname_l(entry, file->uname.s,
		archive_strlen(&(file->uname)), xar->sconv) != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Uname");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Uname cannot be converted from %s to current locale.",
		    archive_string_conversion_charset_name(xar->sconv));
		r = ARCHIVE_WARN;
	}
	archive_entry_set_mode(entry, file->mode);
	if (archive_entry_copy_pathname_l(entry, file->pathname.s,
	    archive_strlen(&(file->pathname)), xar->sconv) != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Pathname");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Pathname cannot be converted from %s to current locale.",
		    archive_string_conversion_charset_name(xar->sconv));
		r = ARCHIVE_WARN;
	}


	if (file->symlink.length > 0 &&
	    archive_entry_copy_symlink_l(entry, file->symlink.s,
		archive_strlen(&(file->symlink)), xar->sconv) != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Linkname");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Linkname cannot be converted from %s to current locale.",
		    archive_string_conversion_charset_name(xar->sconv));
		r = ARCHIVE_WARN;
	}
	/* Set proper nlink. */
	if ((file->mode & AE_IFMT) == AE_IFDIR)
		archive_entry_set_nlink(entry, file->subdirs + 2);
	else
		archive_entry_set_nlink(entry, file->nlink);
	archive_entry_set_size(entry, file->size);
	if (archive_strlen(&(file->hardlink)) > 0)
		archive_entry_set_hardlink(entry, file->hardlink.s);
	archive_entry_set_ino64(entry, file->ino64);
	if (file->has & HAS_DEV)
		archive_entry_set_dev(entry, file->dev);
	if (file->has & HAS_DEVMAJOR)
		archive_entry_set_devmajor(entry, file->devmajor);
	if (file->has & HAS_DEVMINOR)
		archive_entry_set_devminor(entry, file->devminor);
	if (archive_strlen(&(file->fflags_text)) > 0)
		archive_entry_copy_fflags_text(entry, file->fflags_text.s);

	xar->entry_init = 1;
	xar->entry_total = 0;
	xar->entry_remaining = file->length;
	xar->entry_size = file->size;
	xar->entry_encoding = file->encoding;
	xar->entry_a_sum = file->a_sum;
	xar->entry_e_sum = file->e_sum;
	/*
	 * Read extended attributes.
	 */
	xattr = file->xattr_list;
	while (xattr != NULL) {
		const void *d;
		size_t outbytes, used;

		r = move_reading_point(a, xattr->offset);
		if (r != ARCHIVE_OK)
			break;
		r = rd_contents_init(a, xattr->encoding,
		    xattr->a_sum.alg, xattr->e_sum.alg);
		if (r != ARCHIVE_OK)
			break;
		d = NULL;
		r = rd_contents(a, &d, &outbytes, &used, xattr->length);
		if (r != ARCHIVE_OK)
			break;
		if (outbytes != xattr->size) {
			archive_set_error(&(a->archive), ARCHIVE_ERRNO_MISC,
			    "Decompressed size error");
			r = ARCHIVE_FATAL;
			break;
		}
		r = checksum_final(a,
		    xattr->a_sum.val, xattr->a_sum.len,
		    xattr->e_sum.val, xattr->e_sum.len);
		if (r != ARCHIVE_OK)
			break;
		archive_entry_xattr_add_entry(entry,
		    xattr->name.s, d, outbytes);
		xattr = xattr->next;
	}
	if (r != ARCHIVE_OK) {
		file_free(file);
		return (r);
	}

	if (xar->entry_remaining > 0)
		/* Move reading point to the beginning of current
		 * file contents. */
		r = move_reading_point(a, file->offset);
	else
		r = ARCHIVE_OK;

	file_free(file);
	return (r);
}
