static int proc_single_open(struct inode *inode, struct file *filp)
{
	int ret;
	ret = single_open(filp, proc_single_show, NULL);
	if (!ret) {
		struct seq_file *m = filp->private_data;

		m->private = inode;
	}
	return ret;
}
