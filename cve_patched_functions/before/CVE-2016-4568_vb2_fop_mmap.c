int vb2_fop_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct video_device *vdev = video_devdata(file);

	return vb2_mmap(vdev->queue, vma);
}
