stack_max_size_read(struct file *filp, char __user *ubuf,
		    size_t count, loff_t *ppos)
{
	unsigned long *ptr = filp->private_data;
	char buf[64];
	int r;

	r = snprintf(buf, sizeof(buf), "%ld\n", *ptr);
	if (r > sizeof(buf))
		r = sizeof(buf);
	return simple_read_from_buffer(ubuf, count, ppos, buf, r);
}
