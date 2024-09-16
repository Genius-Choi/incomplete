void sas_suspend_sata(struct asd_sas_port *port)
{
	struct domain_device *dev;

	mutex_lock(&port->ha->disco_mutex);
	list_for_each_entry(dev, &port->dev_list, dev_list_node) {
		struct sata_device *sata;

		if (!dev_is_sata(dev))
			continue;

		sata = &dev->sata_dev;
		if (sata->ap->pm_mesg.event == PM_EVENT_SUSPEND)
			continue;

		ata_sas_port_suspend(sata->ap);
	}
	mutex_unlock(&port->ha->disco_mutex);

	sas_ata_flush_pm_eh(port, __func__);
}
