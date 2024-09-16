static int fuse_device_clone(struct fuse_conn *fc, struct file *new)
{
	struct fuse_dev *fud;

	if (new->private_data)
		return -EINVAL;

	fud = fuse_dev_alloc(fc);
	if (!fud)
		return -ENOMEM;

	new->private_data = fud;
	atomic_inc(&fc->dev_count);

	return 0;
}
