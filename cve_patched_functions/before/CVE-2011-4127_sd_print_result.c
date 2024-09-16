static void sd_print_result(struct scsi_disk *sdkp, int result)
{
	sd_printk(KERN_INFO, sdkp, " ");
	scsi_show_result(result);
}
