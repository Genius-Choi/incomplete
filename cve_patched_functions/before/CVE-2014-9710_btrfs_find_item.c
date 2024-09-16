int btrfs_find_item(struct btrfs_root *fs_root, struct btrfs_path *found_path,
		u64 iobjectid, u64 ioff, u8 key_type,
		struct btrfs_key *found_key)
{
	int ret;
	struct btrfs_key key;
	struct extent_buffer *eb;
	struct btrfs_path *path;

	key.type = key_type;
	key.objectid = iobjectid;
	key.offset = ioff;

	if (found_path == NULL) {
		path = btrfs_alloc_path();
		if (!path)
			return -ENOMEM;
	} else
		path = found_path;

	ret = btrfs_search_slot(NULL, fs_root, &key, path, 0, 0);
	if ((ret < 0) || (found_key == NULL)) {
		if (path != found_path)
			btrfs_free_path(path);
		return ret;
	}

	eb = path->nodes[0];
	if (ret && path->slots[0] >= btrfs_header_nritems(eb)) {
		ret = btrfs_next_leaf(fs_root, path);
		if (ret)
			return ret;
		eb = path->nodes[0];
	}

	btrfs_item_key_to_cpu(eb, found_key, path->slots[0]);
	if (found_key->type != key.type ||
			found_key->objectid != key.objectid)
		return 1;

	return 0;
}
