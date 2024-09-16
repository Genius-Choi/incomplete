static void sas_ata_sched_eh(struct ata_port *ap)
{
	struct domain_device *dev = ap->private_data;
	struct sas_ha_struct *ha = dev->port->ha;
	unsigned long flags;

	spin_lock_irqsave(&ha->lock, flags);
	if (!test_and_set_bit(SAS_DEV_EH_PENDING, &dev->state))
		ha->eh_active++;
	ata_std_sched_eh(ap);
	spin_unlock_irqrestore(&ha->lock, flags);
}
