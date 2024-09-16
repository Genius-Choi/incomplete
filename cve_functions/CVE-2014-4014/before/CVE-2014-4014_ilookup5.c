struct inode *ilookup5(struct super_block *sb, unsigned long hashval,
		int (*test)(struct inode *, void *), void *data)
{
	struct inode *inode = ilookup5_nowait(sb, hashval, test, data);

	if (inode)
		wait_on_inode(inode);
	return inode;
}
