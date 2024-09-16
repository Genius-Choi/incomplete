static int aac_change_queue_depth(struct scsi_device *sdev, int depth,
				  int reason)
{
	if (reason != SCSI_QDEPTH_DEFAULT)
		return -EOPNOTSUPP;

	if (sdev->tagged_supported && (sdev->type == TYPE_DISK) &&
	    (sdev_channel(sdev) == CONTAINER_CHANNEL)) {
		struct scsi_device * dev;
		struct Scsi_Host *host = sdev->host;
		unsigned num = 0;

		__shost_for_each_device(dev, host) {
			if (dev->tagged_supported && (dev->type == TYPE_DISK) &&
			    (sdev_channel(dev) == CONTAINER_CHANNEL))
				++num;
			++num;
		}
		if (num >= host->can_queue)
			num = host->can_queue - 1;
		if (depth > (host->can_queue - num))
			depth = host->can_queue - num;
		if (depth > 256)
			depth = 256;
		else if (depth < 2)
			depth = 2;
		scsi_adjust_queue_depth(sdev, MSG_ORDERED_TAG, depth);
	} else
		scsi_adjust_queue_depth(sdev, 0, 1);
	return sdev->queue_depth;
}
