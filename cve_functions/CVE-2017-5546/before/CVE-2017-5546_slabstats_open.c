static int slabstats_open(struct inode *inode, struct file *file)
{
	unsigned long *n;

	n = __seq_open_private(file, &slabstats_op, PAGE_SIZE);
	if (!n)
		return -ENOMEM;

	*n = PAGE_SIZE / (2 * sizeof(unsigned long));

	return 0;
}
