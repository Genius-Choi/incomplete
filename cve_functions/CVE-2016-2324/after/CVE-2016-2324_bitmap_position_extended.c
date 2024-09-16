static inline int bitmap_position_extended(const unsigned char *sha1)
{
	khash_sha1_pos *positions = bitmap_git.ext_index.positions;
	khiter_t pos = kh_get_sha1_pos(positions, sha1);

	if (pos < kh_end(positions)) {
		int bitmap_pos = kh_value(positions, pos);
		return bitmap_pos + bitmap_git.pack->num_objects;
	}

	return -1;
}
