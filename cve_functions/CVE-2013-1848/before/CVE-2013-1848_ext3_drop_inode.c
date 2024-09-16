static int ext3_drop_inode(struct inode *inode)
{
	int drop = generic_drop_inode(inode);

	trace_ext3_drop_inode(inode, drop);
	return drop;
}
