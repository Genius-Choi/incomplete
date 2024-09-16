static int raw_v4_seq_open(struct inode *inode, struct file *file)
{
	return raw_seq_open(inode, file, &raw_v4_hashinfo, &raw_seq_ops);
}
