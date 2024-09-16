static int bpf_map_release(struct inode *inode, struct file *filp)
{
	bpf_map_put_with_uref(filp->private_data);
	return 0;
}
