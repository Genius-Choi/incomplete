tree_mod_log_set_node_key(struct btrfs_fs_info *fs_info,
			  struct extent_buffer *eb, int slot, int atomic)
{
	int ret;

	ret = tree_mod_log_insert_key(fs_info, eb, slot,
					MOD_LOG_KEY_REPLACE,
					atomic ? GFP_ATOMIC : GFP_NOFS);
	BUG_ON(ret < 0);
}
