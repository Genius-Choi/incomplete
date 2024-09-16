static void vop_bh_handler(struct work_struct *work)
{
	struct vop_vdev *vdev = container_of(work, struct vop_vdev,
			virtio_bh_work);

	if (vdev->dc->used_address_updated)
		vop_virtio_init_post(vdev);

	if (vdev->dc->vdev_reset)
		vop_virtio_device_reset(vdev);

	vdev->poll_wake = 1;
	wake_up(&vdev->waitq);
}
