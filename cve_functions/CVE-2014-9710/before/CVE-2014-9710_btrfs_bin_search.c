int btrfs_bin_search(struct extent_buffer *eb, struct btrfs_key *key,
		     int level, int *slot)
{
	return bin_search(eb, key, level, slot);
}
