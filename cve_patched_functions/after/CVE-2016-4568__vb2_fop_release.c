int _vb2_fop_release(struct file *file, struct mutex *lock)
{
	struct video_device *vdev = video_devdata(file);

	if (lock)
		mutex_lock(lock);
	if (file->private_data == vdev->queue->owner) {
		vb2_queue_release(vdev->queue);
		vdev->queue->owner = NULL;
	}
	if (lock)
		mutex_unlock(lock);
	return v4l2_fh_release(file);
}
