int sas_ata_init(struct domain_device *found_dev)
{
	struct sas_ha_struct *ha = found_dev->port->ha;
	struct Scsi_Host *shost = ha->core.shost;
	struct ata_port *ap;
	int rc;

	ata_host_init(&found_dev->sata_dev.ata_host, ha->dev, &sas_sata_ops);
	ap = ata_sas_port_alloc(&found_dev->sata_dev.ata_host,
				&sata_port_info,
				shost);
	if (!ap) {
		SAS_DPRINTK("ata_sas_port_alloc failed.\n");
		return -ENODEV;
	}

	ap->private_data = found_dev;
	ap->cbl = ATA_CBL_SATA;
	ap->scsi_host = shost;
	rc = ata_sas_port_init(ap);
	if (rc) {
		ata_sas_port_destroy(ap);
		return rc;
	}
	found_dev->sata_dev.ap = ap;

	return 0;
}
