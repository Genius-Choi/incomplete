osf_cdfs_mount(char *dirname, struct cdfs_args __user *args, int flags)
{
	int retval;
	struct cdfs_args tmp;
	char *devname;

	retval = -EFAULT;
	if (copy_from_user(&tmp, args, sizeof(tmp)))
		goto out;
	devname = getname(tmp.devname);
	retval = PTR_ERR(devname);
	if (IS_ERR(devname))
		goto out;
	retval = do_mount(devname, dirname, "iso9660", flags, NULL);
	putname(devname);
 out:
	return retval;
}
