static int sas_ata_hard_reset(struct ata_link *link, unsigned int *class,
			      unsigned long deadline)
{
	int ret = 0, res;
	struct sas_phy *phy;
	struct ata_port *ap = link->ap;
	int (*check_ready)(struct ata_link *link);
	struct domain_device *dev = ap->private_data;
	struct sas_internal *i = dev_to_sas_internal(dev);

	res = i->dft->lldd_I_T_nexus_reset(dev);
	if (res == -ENODEV)
		return res;

	if (res != TMF_RESP_FUNC_COMPLETE)
		sas_ata_printk(KERN_DEBUG, dev, "Unable to reset ata device?\n");

	phy = sas_get_local_phy(dev);
	if (scsi_is_sas_phy_local(phy))
		check_ready = local_ata_check_ready;
	else
		check_ready = smp_ata_check_ready;
	sas_put_local_phy(phy);

	ret = ata_wait_after_reset(link, deadline, check_ready);
	if (ret && ret != -EAGAIN)
		sas_ata_printk(KERN_ERR, dev, "reset failed (errno=%d)\n", ret);

	*class = dev->sata_dev.class;

	ap->cbl = ATA_CBL_SATA;
	return ret;
}
