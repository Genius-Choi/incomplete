void test_bitmap_walk(struct rev_info *revs)
{
	struct object *root;
	struct bitmap *result = NULL;
	khiter_t pos;
	size_t result_popcnt;
	struct bitmap_test_data tdata;

	if (prepare_bitmap_git())
		die("failed to load bitmap indexes");

	if (revs->pending.nr != 1)
		die("you must specify exactly one commit to test");

	fprintf(stderr, "Bitmap v%d test (%d entries loaded)\n",
		bitmap_git.version, bitmap_git.entry_count);

	root = revs->pending.objects[0].item;
	pos = kh_get_sha1(bitmap_git.bitmaps, root->oid.hash);

	if (pos < kh_end(bitmap_git.bitmaps)) {
		struct stored_bitmap *st = kh_value(bitmap_git.bitmaps, pos);
		struct ewah_bitmap *bm = lookup_stored_bitmap(st);

		fprintf(stderr, "Found bitmap for %s. %d bits / %08x checksum\n",
			oid_to_hex(&root->oid), (int)bm->bit_size, ewah_checksum(bm));

		result = ewah_to_bitmap(bm);
	}

	if (result == NULL)
		die("Commit %s doesn't have an indexed bitmap", oid_to_hex(&root->oid));

	revs->tag_objects = 1;
	revs->tree_objects = 1;
	revs->blob_objects = 1;

	result_popcnt = bitmap_popcount(result);

	if (prepare_revision_walk(revs))
		die("revision walk setup failed");

	tdata.base = bitmap_new();
	tdata.prg = start_progress("Verifying bitmap entries", result_popcnt);
	tdata.seen = 0;

	traverse_commit_list(revs, &test_show_commit, &test_show_object, &tdata);

	stop_progress(&tdata.prg);

	if (bitmap_equals(result, tdata.base))
		fprintf(stderr, "OK!\n");
	else
		fprintf(stderr, "Mismatch!\n");

	bitmap_free(result);
}
