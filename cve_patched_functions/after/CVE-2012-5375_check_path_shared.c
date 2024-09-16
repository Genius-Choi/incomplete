static int check_path_shared(struct btrfs_root *root,
			     struct btrfs_path *path)
{
	struct extent_buffer *eb;
	int level;
	u64 refs = 1;

	for (level = 0; level < BTRFS_MAX_LEVEL; level++) {
		int ret;

		if (!path->nodes[level])
			break;
		eb = path->nodes[level];
		if (!btrfs_block_can_be_shared(root, eb))
			continue;
		ret = btrfs_lookup_extent_info(NULL, root, eb->start, eb->len,
					       &refs, NULL);
		if (refs > 1)
			return 1;
	}
	return 0;
}
