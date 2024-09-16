static inline int bitmap_position_packfile(const unsigned char *sha1)
{
	off_t offset = find_pack_entry_one(sha1, bitmap_git.pack);
	if (!offset)
		return -1;

	return find_revindex_position(bitmap_git.pack, offset);
}
