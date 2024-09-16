static noinline int mmc_ioctl_dvd_auth(struct cdrom_device_info *cdi,
				       void __user *arg)
{
	int ret;
	dvd_authinfo ai;
	if (!CDROM_CAN(CDC_DVD))
		return -ENOSYS;
	cd_dbg(CD_DO_IOCTL, "entering DVD_AUTH\n");
	if (copy_from_user(&ai, (dvd_authinfo __user *)arg, sizeof(ai)))
		return -EFAULT;
	ret = dvd_do_auth(cdi, &ai);
	if (ret)
		return ret;
	if (copy_to_user((dvd_authinfo __user *)arg, &ai, sizeof(ai)))
		return -EFAULT;
	return 0;
}
