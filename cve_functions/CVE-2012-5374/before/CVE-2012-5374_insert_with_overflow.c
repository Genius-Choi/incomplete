static struct btrfs_dir_item *insert_with_overflow(struct btrfs_trans_handle
						   *trans,
						   struct btrfs_root *root,
						   struct btrfs_path *path,
						   struct btrfs_key *cpu_key,
						   u32 data_size,
						   const char *name,
						   int name_len)
{
	int ret;
	char *ptr;
	struct btrfs_item *item;
	struct extent_buffer *leaf;

	ret = btrfs_insert_empty_item(trans, root, path, cpu_key, data_size);
	if (ret == -EEXIST) {
		struct btrfs_dir_item *di;
		di = btrfs_match_dir_item_name(root, path, name, name_len);
		if (di)
			return ERR_PTR(-EEXIST);
		btrfs_extend_item(trans, root, path, data_size);
	} else if (ret < 0)
		return ERR_PTR(ret);
	WARN_ON(ret > 0);
	leaf = path->nodes[0];
	item = btrfs_item_nr(leaf, path->slots[0]);
	ptr = btrfs_item_ptr(leaf, path->slots[0], char);
	BUG_ON(data_size > btrfs_item_size(leaf, item));
	ptr += btrfs_item_size(leaf, item) - data_size;
	return (struct btrfs_dir_item *)ptr;
}
