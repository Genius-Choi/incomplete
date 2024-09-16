static int sas_get_ata_command_set(struct domain_device *dev)
{
	struct dev_to_host_fis *fis =
		(struct dev_to_host_fis *) dev->frame_rcvd;
	struct ata_taskfile tf;

	if (dev->dev_type == SAS_SATA_PENDING)
		return ATA_DEV_UNKNOWN;

	ata_tf_from_fis((const u8 *)fis, &tf);

	return ata_dev_classify(&tf);
}
