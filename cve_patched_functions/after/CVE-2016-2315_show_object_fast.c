static int show_object_fast(
	const unsigned char *sha1,
	enum object_type type,
	int exclude,
	uint32_t name_hash,
	struct packed_git *found_pack,
	off_t found_offset)
{
	fprintf(stdout, "%s\n", sha1_to_hex(sha1));
	return 1;
}
