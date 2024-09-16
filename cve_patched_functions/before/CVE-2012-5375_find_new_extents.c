static int find_new_extents(struct btrfs_root *root,
			    struct inode *inode, u64 newer_than,
			    u64 *off, int thresh)
{
	struct btrfs_path *path;
	struct btrfs_key min_key;
	struct btrfs_key max_key;
	struct extent_buffer *leaf;
	struct btrfs_file_extent_item *extent;
	int type;
	int ret;
	u64 ino = btrfs_ino(inode);

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	min_key.objectid = ino;
	min_key.type = BTRFS_EXTENT_DATA_KEY;
	min_key.offset = *off;

	max_key.objectid = ino;
	max_key.type = (u8)-1;
	max_key.offset = (u64)-1;

	path->keep_locks = 1;

	while(1) {
		ret = btrfs_search_forward(root, &min_key, &max_key,
					   path, 0, newer_than);
		if (ret != 0)
			goto none;
		if (min_key.objectid != ino)
			goto none;
		if (min_key.type != BTRFS_EXTENT_DATA_KEY)
			goto none;

		leaf = path->nodes[0];
		extent = btrfs_item_ptr(leaf, path->slots[0],
					struct btrfs_file_extent_item);

		type = btrfs_file_extent_type(leaf, extent);
		if (type == BTRFS_FILE_EXTENT_REG &&
		    btrfs_file_extent_num_bytes(leaf, extent) < thresh &&
		    check_defrag_in_cache(inode, min_key.offset, thresh)) {
			*off = min_key.offset;
			btrfs_free_path(path);
			return 0;
		}

		if (min_key.offset == (u64)-1)
			goto none;

		min_key.offset++;
		btrfs_release_path(path);
	}
none:
	btrfs_free_path(path);
	return -ENOENT;
}
