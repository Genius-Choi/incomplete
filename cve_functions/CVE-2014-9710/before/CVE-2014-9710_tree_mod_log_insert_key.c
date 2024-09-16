tree_mod_log_insert_key(struct btrfs_fs_info *fs_info,
			struct extent_buffer *eb, int slot,
			enum mod_log_op op, gfp_t flags)
{
	struct tree_mod_elem *tm;
	int ret;

	if (!tree_mod_need_log(fs_info, eb))
		return 0;

	tm = alloc_tree_mod_elem(eb, slot, op, flags);
	if (!tm)
		return -ENOMEM;

	if (tree_mod_dont_log(fs_info, eb)) {
		kfree(tm);
		return 0;
	}

	ret = __tree_mod_log_insert(fs_info, tm);
	tree_mod_log_write_unlock(fs_info);
	if (ret)
		kfree(tm);

	return ret;
}
