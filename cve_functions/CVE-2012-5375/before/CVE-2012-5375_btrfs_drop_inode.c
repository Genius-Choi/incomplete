int btrfs_drop_inode(struct inode *inode)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;

	if (btrfs_root_refs(&root->root_item) == 0 &&
	    !btrfs_is_free_space_inode(inode))
		return 1;
	else
		return generic_drop_inode(inode);
}
