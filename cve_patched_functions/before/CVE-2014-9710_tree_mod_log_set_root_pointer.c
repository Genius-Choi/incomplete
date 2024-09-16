tree_mod_log_set_root_pointer(struct btrfs_root *root,
			      struct extent_buffer *new_root_node,
			      int log_removal)
{
	int ret;
	ret = tree_mod_log_insert_root(root->fs_info, root->node,
				       new_root_node, GFP_NOFS, log_removal);
	BUG_ON(ret < 0);
}
