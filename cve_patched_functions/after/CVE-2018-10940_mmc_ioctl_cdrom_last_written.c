static noinline int mmc_ioctl_cdrom_last_written(struct cdrom_device_info *cdi,
						 void __user *arg)
{
	int ret;
	long last = 0;
	cd_dbg(CD_DO_IOCTL, "entering CDROM_LAST_WRITTEN\n");
	ret = cdrom_get_last_written(cdi, &last);
	if (ret)
		return ret;
	if (copy_to_user((long __user *)arg, &last, sizeof(last)))
		return -EFAULT;
	return 0;
}
