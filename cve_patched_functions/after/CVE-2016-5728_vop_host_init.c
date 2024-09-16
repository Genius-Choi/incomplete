int vop_host_init(struct vop_info *vi)
{
	int rc;
	struct miscdevice *mdev;
	struct vop_device *vpdev = vi->vpdev;

	INIT_LIST_HEAD(&vi->vdev_list);
	vi->dma_ch = vpdev->dma_ch;
	mdev = &vi->miscdev;
	mdev->minor = MISC_DYNAMIC_MINOR;
	snprintf(vi->name, sizeof(vi->name), "vop_virtio%d", vpdev->index);
	mdev->name = vi->name;
	mdev->fops = &vop_fops;
	mdev->parent = &vpdev->dev;

	rc = misc_register(mdev);
	if (rc)
		dev_err(&vpdev->dev, "%s failed rc %d\n", __func__, rc);
	return rc;
}
