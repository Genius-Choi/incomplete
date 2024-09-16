static inline void tree_mod_log_write_lock(struct btrfs_fs_info *fs_info)
{
	write_lock(&fs_info->tree_mod_log_lock);
}
