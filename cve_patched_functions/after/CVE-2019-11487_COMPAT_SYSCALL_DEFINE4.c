COMPAT_SYSCALL_DEFINE4(vmsplice, int, fd, const struct compat_iovec __user *, iov32,
		    unsigned int, nr_segs, unsigned int, flags)
{
	struct iovec iovstack[UIO_FASTIOV];
	struct iovec *iov = iovstack;
	struct iov_iter iter;
	long error;
	struct fd f;
	int type;

	f = fdget(fd);
	error = vmsplice_type(f, &type);
	if (error)
		return error;

	error = compat_import_iovec(type, iov32, nr_segs,
			     ARRAY_SIZE(iovstack), &iov, &iter);
	if (!error) {
		error = do_vmsplice(f.file, &iter, flags);
		kfree(iov);
	}
	fdput(f);
	return error;
}
