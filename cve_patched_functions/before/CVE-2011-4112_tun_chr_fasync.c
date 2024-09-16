static int tun_chr_fasync(int fd, struct file *file, int on)
{
	struct tun_struct *tun = tun_get(file);
	int ret;

	if (!tun)
		return -EBADFD;

	tun_debug(KERN_INFO, tun, "tun_chr_fasync %d\n", on);

	if ((ret = fasync_helper(fd, file, on, &tun->fasync)) < 0)
		goto out;

	if (on) {
		ret = __f_setown(file, task_pid(current), PIDTYPE_PID, 0);
		if (ret)
			goto out;
		tun->flags |= TUN_FASYNC;
	} else
		tun->flags &= ~TUN_FASYNC;
	ret = 0;
out:
	tun_put(tun);
	return ret;
}
