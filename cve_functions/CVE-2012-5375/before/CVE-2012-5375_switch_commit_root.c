static noinline void switch_commit_root(struct btrfs_root *root)
{
	free_extent_buffer(root->commit_root);
	root->commit_root = btrfs_root_node(root);
}
