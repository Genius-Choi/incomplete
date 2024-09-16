static int ui_open(struct inode *inode, struct file *filp)
{
	struct hfi1_devdata *dd;

	dd = container_of(inode->i_cdev, struct hfi1_devdata, ui_cdev);
	filp->private_data = dd; /* for other methods */
	return 0;
}
