static int __init blk_scsi_ioctl_init(void)
{
	blk_set_cmd_filter_defaults(&blk_default_cmd_filter);
	return 0;
}
