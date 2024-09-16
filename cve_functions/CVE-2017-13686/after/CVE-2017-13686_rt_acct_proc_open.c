static int rt_acct_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, rt_acct_proc_show, NULL);
}
