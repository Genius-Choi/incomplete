void sas_ata_end_eh(struct ata_port *ap)
{
	struct domain_device *dev = ap->private_data;
	struct sas_ha_struct *ha = dev->port->ha;
	unsigned long flags;

	spin_lock_irqsave(&ha->lock, flags);
	if (test_and_clear_bit(SAS_DEV_EH_PENDING, &dev->state))
		ha->eh_active--;
	spin_unlock_irqrestore(&ha->lock, flags);
}
