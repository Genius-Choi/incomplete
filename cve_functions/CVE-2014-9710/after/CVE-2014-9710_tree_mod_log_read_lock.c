static inline void tree_mod_log_read_lock(struct btrfs_fs_info *fs_info)
{
	read_lock(&fs_info->tree_mod_log_lock);
}
