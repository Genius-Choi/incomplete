static int load_pack_bitmap(void)
{
	assert(bitmap_git.map && !bitmap_git.loaded);

	bitmap_git.bitmaps = kh_init_sha1();
	bitmap_git.ext_index.positions = kh_init_sha1_pos();
	load_pack_revindex(bitmap_git.pack);

	if (!(bitmap_git.commits = read_bitmap_1(&bitmap_git)) ||
		!(bitmap_git.trees = read_bitmap_1(&bitmap_git)) ||
		!(bitmap_git.blobs = read_bitmap_1(&bitmap_git)) ||
		!(bitmap_git.tags = read_bitmap_1(&bitmap_git)))
		goto failed;

	if (load_bitmap_entries_v1(&bitmap_git) < 0)
		goto failed;

	bitmap_git.loaded = 1;
	return 0;

failed:
	munmap(bitmap_git.map, bitmap_git.map_size);
	bitmap_git.map = NULL;
	bitmap_git.map_size = 0;
	return -1;
}
