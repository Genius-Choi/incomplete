static int tracing_time_stamp_mode_open(struct inode *inode, struct file *file)
{
	struct trace_array *tr = inode->i_private;
	int ret;

	if (tracing_disabled)
		return -ENODEV;

	if (trace_array_get(tr))
		return -ENODEV;

	ret = single_open(file, tracing_time_stamp_mode_show, inode->i_private);
	if (ret < 0)
		trace_array_put(tr);

	return ret;
}
