static const char *create_index(void)
{
	const char *tmpfile;
	struct pack_idx_entry **idx, **c, **last;
	struct object_entry *e;
	struct object_entry_pool *o;

	/* Build the table of object IDs. */
	idx = xmalloc(object_count * sizeof(*idx));
	c = idx;
	for (o = blocks; o; o = o->next_pool)
		for (e = o->next_free; e-- != o->entries;)
			if (pack_id == e->pack_id)
				*c++ = &e->idx;
	last = idx + object_count;
	if (c != last)
		die("internal consistency error creating the index");

	tmpfile = write_idx_file(NULL, idx, object_count, &pack_idx_opts, pack_data->sha1);
	free(idx);
	return tmpfile;
}
