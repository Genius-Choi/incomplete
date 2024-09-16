int rebuild_existing_bitmaps(struct packing_data *mapping,
			     khash_sha1 *reused_bitmaps,
			     int show_progress)
{
	uint32_t i, num_objects;
	uint32_t *reposition;
	struct bitmap *rebuild;
	struct stored_bitmap *stored;
	struct progress *progress = NULL;

	khiter_t hash_pos;
	int hash_ret;

	if (prepare_bitmap_git() < 0)
		return -1;

	num_objects = bitmap_git.pack->num_objects;
	reposition = xcalloc(num_objects, sizeof(uint32_t));

	for (i = 0; i < num_objects; ++i) {
		const unsigned char *sha1;
		struct revindex_entry *entry;
		struct object_entry *oe;

		entry = &bitmap_git.pack->revindex[i];
		sha1 = nth_packed_object_sha1(bitmap_git.pack, entry->nr);
		oe = packlist_find(mapping, sha1, NULL);

		if (oe)
			reposition[i] = oe->in_pack_pos + 1;
	}

	rebuild = bitmap_new();
	i = 0;

	if (show_progress)
		progress = start_progress("Reusing bitmaps", 0);

	kh_foreach_value(bitmap_git.bitmaps, stored, {
		if (stored->flags & BITMAP_FLAG_REUSE) {
			if (!rebuild_bitmap(reposition,
					    lookup_stored_bitmap(stored),
					    rebuild)) {
				hash_pos = kh_put_sha1(reused_bitmaps,
						       stored->sha1,
						       &hash_ret);
				kh_value(reused_bitmaps, hash_pos) =
					bitmap_to_ewah(rebuild);
			}
			bitmap_reset(rebuild);
			display_progress(progress, ++i);
		}
	});

	stop_progress(&progress);

	free(reposition);
	bitmap_free(rebuild);
	return 0;
}
