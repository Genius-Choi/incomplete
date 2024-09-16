buffer_percent_read(struct file *filp, char __user *ubuf,
		    size_t cnt, loff_t *ppos)
{
	struct trace_array *tr = filp->private_data;
	char buf[64];
	int r;

	r = tr->buffer_percent;
	r = sprintf(buf, "%d\n", r);

	return simple_read_from_buffer(ubuf, cnt, ppos, buf, r);
}
