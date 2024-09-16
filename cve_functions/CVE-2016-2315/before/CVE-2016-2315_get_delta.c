static void *get_delta(struct object_entry *entry)
{
	unsigned long size, base_size, delta_size;
	void *buf, *base_buf, *delta_buf;
	enum object_type type;

	buf = read_sha1_file(entry->idx.sha1, &type, &size);
	if (!buf)
		die("unable to read %s", sha1_to_hex(entry->idx.sha1));
	base_buf = read_sha1_file(entry->delta->idx.sha1, &type, &base_size);
	if (!base_buf)
		die("unable to read %s", sha1_to_hex(entry->delta->idx.sha1));
	delta_buf = diff_delta(base_buf, base_size,
			       buf, size, &delta_size, 0);
	if (!delta_buf || delta_size != entry->delta_size)
		die("delta size changed");
	free(buf);
	free(base_buf);
	return delta_buf;
}
