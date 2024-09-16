static int sd_remove(struct device *dev)
{
	struct scsi_disk *sdkp;

	sdkp = dev_get_drvdata(dev);
	scsi_autopm_get_device(sdkp->device);

	async_synchronize_full();
	blk_queue_prep_rq(sdkp->device->request_queue, scsi_prep_fn);
	blk_queue_unprep_rq(sdkp->device->request_queue, NULL);
	device_del(&sdkp->dev);
	del_gendisk(sdkp->disk);
	sd_shutdown(dev);

	mutex_lock(&sd_ref_mutex);
	dev_set_drvdata(dev, NULL);
	put_device(&sdkp->dev);
	mutex_unlock(&sd_ref_mutex);

	return 0;
}
