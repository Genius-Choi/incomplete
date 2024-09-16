static int add_object_entry_from_bitmap(const unsigned char *sha1,
					enum object_type type,
					int flags, uint32_t name_hash,
					struct packed_git *pack, off_t offset)
{
	uint32_t index_pos;

	if (have_duplicate_entry(sha1, 0, &index_pos))
		return 0;

	create_object_entry(sha1, type, name_hash, 0, 0, index_pos, pack, offset);

	display_progress(progress_state, nr_result);
	return 1;
}
