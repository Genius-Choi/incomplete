static int rt_cache_seq_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &rt_cache_seq_ops);
}
