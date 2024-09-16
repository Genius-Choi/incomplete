void sas_target_destroy(struct scsi_target *starget)
{
	struct domain_device *found_dev = starget->hostdata;

	if (!found_dev)
		return;

	starget->hostdata = NULL;
	sas_put_device(found_dev);
}
