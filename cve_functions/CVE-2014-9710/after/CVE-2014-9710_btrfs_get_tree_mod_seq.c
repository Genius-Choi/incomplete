u64 btrfs_get_tree_mod_seq(struct btrfs_fs_info *fs_info,
			   struct seq_list *elem)
{
	tree_mod_log_write_lock(fs_info);
	spin_lock(&fs_info->tree_mod_seq_lock);
	if (!elem->seq) {
		elem->seq = btrfs_inc_tree_mod_seq(fs_info);
		list_add_tail(&elem->list, &fs_info->tree_mod_seq_list);
	}
	spin_unlock(&fs_info->tree_mod_seq_lock);
	tree_mod_log_write_unlock(fs_info);

	return elem->seq;
}
