static struct ewah_bitmap *find_reused_bitmap(const unsigned char *sha1)
{
	khiter_t hash_pos;

	if (!writer.reused)
		return NULL;

	hash_pos = kh_get_sha1(writer.reused, sha1);
	if (hash_pos >= kh_end(writer.reused))
		return NULL;

	return kh_value(writer.reused, hash_pos);
}
