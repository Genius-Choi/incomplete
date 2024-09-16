static int have_duplicate_entry(const unsigned char *sha1,
				int exclude,
				uint32_t *index_pos)
{
	struct object_entry *entry;

	entry = packlist_find(&to_pack, sha1, index_pos);
	if (!entry)
		return 0;

	if (exclude) {
		if (!entry->preferred_base)
			nr_result--;
		entry->preferred_base = 1;
	}

	return 1;
}
