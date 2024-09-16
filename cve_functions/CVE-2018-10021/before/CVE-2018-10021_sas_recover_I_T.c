static int sas_recover_I_T(struct domain_device *dev)
{
	int res = TMF_RESP_FUNC_FAILED;
	struct sas_internal *i =
		to_sas_internal(dev->port->ha->core.shost->transportt);

	SAS_DPRINTK("I_T nexus reset for dev %016llx\n",
		    SAS_ADDR(dev->sas_addr));

	if (i->dft->lldd_I_T_nexus_reset)
		res = i->dft->lldd_I_T_nexus_reset(dev);

	return res;
}
