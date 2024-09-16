void bitmap_writer_build(struct packing_data *to_pack)
{
	static const double REUSE_BITMAP_THRESHOLD = 0.2;

	int i, reuse_after, need_reset;
	struct bitmap *base = bitmap_new();
	struct rev_info revs;

	writer.bitmaps = kh_init_sha1();
	writer.to_pack = to_pack;

	if (writer.show_progress)
		writer.progress = start_progress("Building bitmaps", writer.selected_nr);

	init_revisions(&revs, NULL);
	revs.tag_objects = 1;
	revs.tree_objects = 1;
	revs.blob_objects = 1;
	revs.no_walk = 0;

	revs.include_check = should_include;
	reset_revision_walk();

	reuse_after = writer.selected_nr * REUSE_BITMAP_THRESHOLD;
	need_reset = 0;

	for (i = writer.selected_nr - 1; i >= 0; --i) {
		struct bitmapped_commit *stored;
		struct object *object;

		khiter_t hash_pos;
		int hash_ret;

		stored = &writer.selected[i];
		object = (struct object *)stored->commit;

		if (stored->bitmap == NULL) {
			if (i < writer.selected_nr - 1 &&
			    (need_reset ||
			     !in_merge_bases(writer.selected[i + 1].commit,
					     stored->commit))) {
			    bitmap_reset(base);
			    reset_all_seen();
			}

			add_pending_object(&revs, object, "");
			revs.include_check_data = base;

			if (prepare_revision_walk(&revs))
				die("revision walk setup failed");

			traverse_commit_list(&revs, show_commit, show_object, base);

			revs.pending.nr = 0;
			revs.pending.alloc = 0;
			revs.pending.objects = NULL;

			stored->bitmap = bitmap_to_ewah(base);
			need_reset = 0;
		} else
			need_reset = 1;

		if (i >= reuse_after)
			stored->flags |= BITMAP_FLAG_REUSE;

		hash_pos = kh_put_sha1(writer.bitmaps, object->oid.hash, &hash_ret);
		if (hash_ret == 0)
			die("Duplicate entry when writing index: %s",
			    oid_to_hex(&object->oid));

		kh_value(writer.bitmaps, hash_pos) = stored;
		display_progress(writer.progress, writer.selected_nr - i);
	}

	bitmap_free(base);
	stop_progress(&writer.progress);

	compute_xor_offsets();
}
