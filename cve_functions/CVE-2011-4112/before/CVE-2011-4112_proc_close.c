static int proc_close( struct inode *inode, struct file *file )
{
	struct proc_data *data = file->private_data;

	if (data->on_close != NULL)
		data->on_close(inode, file);
	kfree(data->rbuffer);
	kfree(data->wbuffer);
	kfree(data);
	return 0;
}
