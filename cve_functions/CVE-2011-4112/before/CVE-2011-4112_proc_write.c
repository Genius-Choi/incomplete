static ssize_t proc_write( struct file *file,
			   const char __user *buffer,
			   size_t len,
			   loff_t *offset )
{
	ssize_t ret;
	struct proc_data *priv = file->private_data;

	if (!priv->wbuffer)
		return -EINVAL;

	ret = simple_write_to_buffer(priv->wbuffer, priv->maxwritelen, offset,
					buffer, len);
	if (ret > 0)
		priv->writelen = max_t(int, priv->writelen, *offset);

	return ret;
}
