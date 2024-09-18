static struct sas_internal *dev_to_sas_internal(struct domain_device *dev)
{
	return to_sas_internal(dev->port->ha->core.shost->transportt);
}
