static int pmcraid_notify_ccn(struct pmcraid_instance *pinstance)
{
	return pmcraid_notify_aen(pinstance,
				pinstance->ccn.msg,
				pinstance->ccn.hcam->data_len +
				sizeof(struct pmcraid_hcam_hdr));
}
