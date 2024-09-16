static int get_xattr_block(long long start)
{
	int hash = start & 0xffff;
	struct hash_entry *hash_entry = hash_table[hash];

	for(; hash_entry; hash_entry = hash_entry->next)
		if(hash_entry->start == start)
			break;

	TRACE("get_xattr_block: start %lld, offset %d\n", start,
		hash_entry ? hash_entry->offset : -1);

	return hash_entry ? hash_entry->offset : -1;
}
