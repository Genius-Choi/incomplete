static int key_search(struct extent_buffer *b, struct btrfs_key *key,
		      int level, int *prev_cmp, int *slot)
{
	if (*prev_cmp != 0) {
		*prev_cmp = bin_search(b, key, level, slot);
		return *prev_cmp;
	}

	key_search_validate(b, key, level);
	*slot = 0;

	return 0;
}
