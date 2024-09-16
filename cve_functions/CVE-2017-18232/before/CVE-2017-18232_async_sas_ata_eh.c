static void async_sas_ata_eh(void *data, async_cookie_t cookie)
{
	struct domain_device *dev = data;
	struct ata_port *ap = dev->sata_dev.ap;
	struct sas_ha_struct *ha = dev->port->ha;

	sas_ata_printk(KERN_DEBUG, dev, "dev error handler\n");
	ata_scsi_port_error_handler(ha->core.shost, ap);
	sas_put_device(dev);
}
