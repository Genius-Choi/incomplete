struct domain_device *sas_find_dev_by_rphy(struct sas_rphy *rphy)
{
	struct Scsi_Host *shost = dev_to_shost(rphy->dev.parent);
	struct sas_ha_struct *ha = SHOST_TO_SAS_HA(shost);
	struct domain_device *found_dev = NULL;
	int i;
	unsigned long flags;

	spin_lock_irqsave(&ha->phy_port_lock, flags);
	for (i = 0; i < ha->num_phys; i++) {
		struct asd_sas_port *port = ha->sas_port[i];
		struct domain_device *dev;

		spin_lock(&port->dev_list_lock);
		list_for_each_entry(dev, &port->dev_list, dev_list_node) {
			if (rphy == dev->rphy) {
				found_dev = dev;
				spin_unlock(&port->dev_list_lock);
				goto found;
			}
		}
		spin_unlock(&port->dev_list_lock);
	}
 found:
	spin_unlock_irqrestore(&ha->phy_port_lock, flags);

	return found_dev;
}
