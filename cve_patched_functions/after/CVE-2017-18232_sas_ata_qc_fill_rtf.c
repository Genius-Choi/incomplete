static bool sas_ata_qc_fill_rtf(struct ata_queued_cmd *qc)
{
	struct domain_device *dev = qc->ap->private_data;

	ata_tf_from_fis(dev->sata_dev.fis, &qc->result_tf);
	return true;
}
