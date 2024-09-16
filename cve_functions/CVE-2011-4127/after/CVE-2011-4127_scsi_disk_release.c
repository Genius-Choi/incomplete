static void scsi_disk_release(struct device *dev)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);
	struct gendisk *disk = sdkp->disk;
	
	spin_lock(&sd_index_lock);
	ida_remove(&sd_index_ida, sdkp->index);
	spin_unlock(&sd_index_lock);

	disk->private_data = NULL;
	put_disk(disk);
	put_device(&sdkp->device->sdev_gendev);

	kfree(sdkp);
}
