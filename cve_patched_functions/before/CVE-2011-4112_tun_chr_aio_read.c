static ssize_t tun_chr_aio_read(struct kiocb *iocb, const struct iovec *iv,
			    unsigned long count, loff_t pos)
{
	struct file *file = iocb->ki_filp;
	struct tun_file *tfile = file->private_data;
	struct tun_struct *tun = __tun_get(tfile);
	ssize_t len, ret;

	if (!tun)
		return -EBADFD;
	len = iov_length(iv, count);
	if (len < 0) {
		ret = -EINVAL;
		goto out;
	}

	ret = tun_do_read(tun, iocb, iv, len, file->f_flags & O_NONBLOCK);
	ret = min_t(ssize_t, ret, len);
out:
	tun_put(tun);
	return ret;
}
