static noinline int btrfs_search_path_in_tree(struct btrfs_fs_info *info,
				u64 tree_id, u64 dirid, char *name)
{
	struct btrfs_root *root;
	struct btrfs_key key;
	char *ptr;
	int ret = -1;
	int slot;
	int len;
	int total_len = 0;
	struct btrfs_inode_ref *iref;
	struct extent_buffer *l;
	struct btrfs_path *path;

	if (dirid == BTRFS_FIRST_FREE_OBJECTID) {
		name[0]='\0';
		return 0;
	}

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	ptr = &name[BTRFS_INO_LOOKUP_PATH_MAX];

	key.objectid = tree_id;
	key.type = BTRFS_ROOT_ITEM_KEY;
	key.offset = (u64)-1;
	root = btrfs_read_fs_root_no_name(info, &key);
	if (IS_ERR(root)) {
		printk(KERN_ERR "could not find root %llu\n", tree_id);
		ret = -ENOENT;
		goto out;
	}

	key.objectid = dirid;
	key.type = BTRFS_INODE_REF_KEY;
	key.offset = (u64)-1;

	while(1) {
		ret = btrfs_search_slot(NULL, root, &key, path, 0, 0);
		if (ret < 0)
			goto out;

		l = path->nodes[0];
		slot = path->slots[0];
		if (ret > 0 && slot > 0)
			slot--;
		btrfs_item_key_to_cpu(l, &key, slot);

		if (ret > 0 && (key.objectid != dirid ||
				key.type != BTRFS_INODE_REF_KEY)) {
			ret = -ENOENT;
			goto out;
		}

		iref = btrfs_item_ptr(l, slot, struct btrfs_inode_ref);
		len = btrfs_inode_ref_name_len(l, iref);
		ptr -= len + 1;
		total_len += len + 1;
		if (ptr < name)
			goto out;

		*(ptr + len) = '/';
		read_extent_buffer(l, ptr,(unsigned long)(iref + 1), len);

		if (key.offset == BTRFS_FIRST_FREE_OBJECTID)
			break;

		btrfs_release_path(path);
		key.objectid = key.offset;
		key.offset = (u64)-1;
		dirid = key.objectid;
	}
	if (ptr < name)
		goto out;
	memmove(name, ptr, total_len);
	name[total_len]='\0';
	ret = 0;
out:
	btrfs_free_path(path);
	return ret;
}
