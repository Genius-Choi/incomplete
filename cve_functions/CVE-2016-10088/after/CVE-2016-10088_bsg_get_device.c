static struct bsg_device *bsg_get_device(struct inode *inode, struct file *file)
{
	struct bsg_device *bd;
	struct bsg_class_device *bcd;

	/*
	 * find the class device
	 */
	mutex_lock(&bsg_mutex);
	bcd = idr_find(&bsg_minor_idr, iminor(inode));
	if (bcd)
		kref_get(&bcd->ref);
	mutex_unlock(&bsg_mutex);

	if (!bcd)
		return ERR_PTR(-ENODEV);

	bd = __bsg_get_device(iminor(inode), bcd->queue);
	if (bd)
		return bd;

	bd = bsg_add_device(inode, bcd->queue, file);
	if (IS_ERR(bd))
		kref_put(&bcd->ref, bsg_kref_release_function);

	return bd;
}
