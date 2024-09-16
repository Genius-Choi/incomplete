static void fixup_inode_flags(struct inode *dir, struct inode *inode)
{
	struct btrfs_inode *b_dir = BTRFS_I(dir);
	struct btrfs_inode *b_inode = BTRFS_I(inode);

	if (b_dir->flags & BTRFS_INODE_NODATACOW)
		b_inode->flags |= BTRFS_INODE_NODATACOW;
	else
		b_inode->flags &= ~BTRFS_INODE_NODATACOW;

	if (b_dir->flags & BTRFS_INODE_COMPRESS) {
		b_inode->flags |= BTRFS_INODE_COMPRESS;
		b_inode->flags &= ~BTRFS_INODE_NOCOMPRESS;
	} else {
		b_inode->flags &= ~(BTRFS_INODE_COMPRESS |
				    BTRFS_INODE_NOCOMPRESS);
	}
}
