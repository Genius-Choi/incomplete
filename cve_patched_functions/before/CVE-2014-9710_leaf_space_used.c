static int leaf_space_used(struct extent_buffer *l, int start, int nr)
{
	struct btrfs_item *start_item;
	struct btrfs_item *end_item;
	struct btrfs_map_token token;
	int data_len;
	int nritems = btrfs_header_nritems(l);
	int end = min(nritems, start + nr) - 1;

	if (!nr)
		return 0;
	btrfs_init_map_token(&token);
	start_item = btrfs_item_nr(start);
	end_item = btrfs_item_nr(end);
	data_len = btrfs_token_item_offset(l, start_item, &token) +
		btrfs_token_item_size(l, start_item, &token);
	data_len = data_len - btrfs_token_item_offset(l, end_item, &token);
	data_len += sizeof(struct btrfs_item) * nr;
	WARN_ON(data_len < 0);
	return data_len;
}
