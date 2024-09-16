re_get_entry(struct iso9660 *iso9660)
{
	struct file_info *file;

	if ((file = iso9660->re_files.first) != NULL) {
		iso9660->re_files.first = file->re_next;
		if (iso9660->re_files.first == NULL)
			iso9660->re_files.last =
			    &(iso9660->re_files.first);
	}
	return (file);
}
