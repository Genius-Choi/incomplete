int sas_ioctl(struct scsi_device *sdev, int cmd, void __user *arg)
{
	struct domain_device *dev = sdev_to_domain_dev(sdev);

	if (dev_is_sata(dev))
		return ata_sas_scsi_ioctl(dev->sata_dev.ap, sdev, cmd, arg);

	return -EINVAL;
}
