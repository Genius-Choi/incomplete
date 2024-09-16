tree_mod_log_eb_move(struct btrfs_fs_info *fs_info, struct extent_buffer *dst,
		     int dst_offset, int src_offset, int nr_items)
{
	int ret;
	ret = tree_mod_log_insert_move(fs_info, dst, dst_offset, src_offset,
				       nr_items, GFP_NOFS);
	BUG_ON(ret < 0);
}
