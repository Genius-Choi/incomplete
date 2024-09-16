void sas_ata_wait_eh(struct domain_device *dev)
{
	struct ata_port *ap;

	if (!dev_is_sata(dev))
		return;

	ap = dev->sata_dev.ap;
	ata_port_wait_eh(ap);
}
