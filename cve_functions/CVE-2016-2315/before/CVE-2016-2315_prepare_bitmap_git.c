int prepare_bitmap_git(void)
{
	if (bitmap_git.loaded)
		return 0;

	if (!open_pack_bitmap())
		return load_pack_bitmap();

	return -1;
}
