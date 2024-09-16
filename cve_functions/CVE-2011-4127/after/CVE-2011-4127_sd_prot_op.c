static void sd_prot_op(struct scsi_cmnd *scmd, unsigned int dif)
{
	unsigned int prot_op = SCSI_PROT_NORMAL;
	unsigned int dix = scsi_prot_sg_count(scmd);

	if (scmd->sc_data_direction == DMA_FROM_DEVICE) {
		if (dif && dix)
			prot_op = SCSI_PROT_READ_PASS;
		else if (dif && !dix)
			prot_op = SCSI_PROT_READ_STRIP;
		else if (!dif && dix)
			prot_op = SCSI_PROT_READ_INSERT;
	} else {
		if (dif && dix)
			prot_op = SCSI_PROT_WRITE_PASS;
		else if (dif && !dix)
			prot_op = SCSI_PROT_WRITE_INSERT;
		else if (!dif && dix)
			prot_op = SCSI_PROT_WRITE_STRIP;
	}

	scsi_set_prot_op(scmd, prot_op);
	scsi_set_prot_type(scmd, dif);
}
