void tmp_proc_unmount(struct lxc_conf *lxc_conf)
{
	if (lxc_conf->tmp_umount_proc == 1) {
		umount("/proc");
		lxc_conf->tmp_umount_proc = 0;
	}
}
