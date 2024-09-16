static ssize_t proc_read( struct file *file,
			  char __user *buffer,
			  size_t len,
			  loff_t *offset )
{
	struct proc_data *priv = file->private_data;

	if (!priv->rbuffer)
		return -EINVAL;

	return simple_read_from_buffer(buffer, len, offset, priv->rbuffer,
					priv->readlen);
}
