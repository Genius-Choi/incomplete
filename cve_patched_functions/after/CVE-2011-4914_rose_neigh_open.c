static int rose_neigh_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &rose_neigh_seqops);
}
