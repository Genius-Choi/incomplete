static const unsigned char *sha1_access(size_t pos, void *table)
{
	struct pack_idx_entry **index = table;
	return index[pos]->sha1;
}
