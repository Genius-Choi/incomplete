static void test_show_commit(struct commit *commit, void *data)
{
	struct bitmap_test_data *tdata = data;
	int bitmap_pos;

	bitmap_pos = bitmap_position(commit->object.oid.hash);
	if (bitmap_pos < 0)
		die("Object not in bitmap: %s\n", oid_to_hex(&commit->object.oid));

	bitmap_set(tdata->base, bitmap_pos);
	display_progress(tdata->prg, ++tdata->seen);
}
