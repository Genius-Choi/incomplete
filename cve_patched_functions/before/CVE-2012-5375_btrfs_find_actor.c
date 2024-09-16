static int btrfs_find_actor(struct inode *inode, void *opaque)
{
	struct btrfs_iget_args *args = opaque;
	return args->ino == btrfs_ino(inode) &&
		args->root == BTRFS_I(inode)->root;
}
