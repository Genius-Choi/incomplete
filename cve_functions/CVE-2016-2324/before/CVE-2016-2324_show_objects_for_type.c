static void show_objects_for_type(
	struct bitmap *objects,
	struct ewah_bitmap *type_filter,
	enum object_type object_type,
	show_reachable_fn show_reach)
{
	size_t pos = 0, i = 0;
	uint32_t offset;

	struct ewah_iterator it;
	eword_t filter;

	if (bitmap_git.reuse_objects == bitmap_git.pack->num_objects)
		return;

	ewah_iterator_init(&it, type_filter);

	while (i < objects->word_alloc && ewah_iterator_next(&filter, &it)) {
		eword_t word = objects->words[i] & filter;

		for (offset = 0; offset < BITS_IN_EWORD; ++offset) {
			const unsigned char *sha1;
			struct revindex_entry *entry;
			uint32_t hash = 0;

			if ((word >> offset) == 0)
				break;

			offset += ewah_bit_ctz64(word >> offset);

			if (pos + offset < bitmap_git.reuse_objects)
				continue;

			entry = &bitmap_git.pack->revindex[pos + offset];
			sha1 = nth_packed_object_sha1(bitmap_git.pack, entry->nr);

			if (bitmap_git.hashes)
				hash = ntohl(bitmap_git.hashes[entry->nr]);

			show_reach(sha1, object_type, 0, hash, bitmap_git.pack, entry->offset);
		}

		pos += BITS_IN_EWORD;
		i++;
	}
}
