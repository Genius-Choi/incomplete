void sas_ata_schedule_reset(struct domain_device *dev)
{
	struct ata_eh_info *ehi;
	struct ata_port *ap;
	unsigned long flags;

	if (!dev_is_sata(dev))
		return;

	ap = dev->sata_dev.ap;
	ehi = &ap->link.eh_info;

	spin_lock_irqsave(ap->lock, flags);
	ehi->err_mask |= AC_ERR_TIMEOUT;
	ehi->action |= ATA_EH_RESET;
	ata_port_schedule_eh(ap);
	spin_unlock_irqrestore(ap->lock, flags);
}
