static void write_hash_cache(struct sha1file *f,
			     struct pack_idx_entry **index,
			     uint32_t index_nr)
{
	uint32_t i;

	for (i = 0; i < index_nr; ++i) {
		struct object_entry *entry = (struct object_entry *)index[i];
		uint32_t hash_value = htonl(entry->hash);
		sha1write(f, &hash_value, sizeof(hash_value));
	}
}
