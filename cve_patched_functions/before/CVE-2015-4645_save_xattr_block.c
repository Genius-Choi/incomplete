static void save_xattr_block(long long start, int offset)
{
	struct hash_entry *hash_entry = malloc(sizeof(*hash_entry));
	int hash = start & 0xffff;

	TRACE("save_xattr_block: start %lld, offset %d\n", start, offset);

	if(hash_entry == NULL)
		MEM_ERROR();

	hash_entry->start = start;
	hash_entry->offset = offset;
	hash_entry->next = hash_table[hash];
	hash_table[hash] = hash_entry;
}
