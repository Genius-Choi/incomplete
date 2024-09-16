void bitmap_writer_reuse_bitmaps(struct packing_data *to_pack)
{
	if (prepare_bitmap_git() < 0)
		return;

	writer.reused = kh_init_sha1();
	rebuild_existing_bitmaps(to_pack, writer.reused, writer.show_progress);
}
