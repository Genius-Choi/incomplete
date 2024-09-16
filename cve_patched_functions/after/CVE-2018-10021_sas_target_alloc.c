int sas_target_alloc(struct scsi_target *starget)
{
	struct sas_rphy *rphy = dev_to_rphy(starget->dev.parent);
	struct domain_device *found_dev = sas_find_dev_by_rphy(rphy);

	if (!found_dev)
		return -ENODEV;

	kref_get(&found_dev->kref);
	starget->hostdata = found_dev;
	return 0;
}
