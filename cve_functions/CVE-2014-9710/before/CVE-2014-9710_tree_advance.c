static int tree_advance(struct btrfs_root *root,
			struct btrfs_path *path,
			int *level, int root_level,
			int allow_down,
			struct btrfs_key *key)
{
	int ret;

	if (*level == 0 || !allow_down) {
		ret = tree_move_next_or_upnext(root, path, level, root_level);
	} else {
		tree_move_down(root, path, level, root_level);
		ret = 0;
	}
	if (ret >= 0) {
		if (*level == 0)
			btrfs_item_key_to_cpu(path->nodes[*level], key,
					path->slots[*level]);
		else
			btrfs_node_key_to_cpu(path->nodes[*level], key,
					path->slots[*level]);
	}
	return ret;
}
