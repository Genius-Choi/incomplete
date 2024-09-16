int btrfs_create_subvol_root(struct btrfs_trans_handle *trans,
			     struct btrfs_root *new_root, u64 new_dirid)
{
	struct inode *inode;
	int err;
	u64 index = 0;

	inode = btrfs_new_inode(trans, new_root, NULL, "..", 2,
				new_dirid, new_dirid,
				S_IFDIR | (~current_umask() & S_IRWXUGO),
				&index);
	if (IS_ERR(inode))
		return PTR_ERR(inode);
	inode->i_op = &btrfs_dir_inode_operations;
	inode->i_fop = &btrfs_dir_file_operations;

	set_nlink(inode, 1);
	btrfs_i_size_write(inode, 0);

	err = btrfs_update_inode(trans, new_root, inode);

	iput(inode);
	return err;
}
