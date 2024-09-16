static void create_object_entry(const unsigned char *sha1,
				enum object_type type,
				uint32_t hash,
				int exclude,
				int no_try_delta,
				uint32_t index_pos,
				struct packed_git *found_pack,
				off_t found_offset)
{
	struct object_entry *entry;

	entry = packlist_alloc(&to_pack, sha1, index_pos);
	entry->hash = hash;
	if (type)
		entry->type = type;
	if (exclude)
		entry->preferred_base = 1;
	else
		nr_result++;
	if (found_pack) {
		entry->in_pack = found_pack;
		entry->in_pack_offset = found_offset;
	}

	entry->no_try_delta = no_try_delta;
}
