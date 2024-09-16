static void sd_print_sense_hdr(struct scsi_disk *sdkp,
			       struct scsi_sense_hdr *sshdr)
{
	sd_printk(KERN_INFO, sdkp, " ");
	scsi_show_sense_hdr(sshdr);
	sd_printk(KERN_INFO, sdkp, " ");
	scsi_show_extd_sense(sshdr->asc, sshdr->ascq);
}
