static struct file *find_readable_file_locked(struct nfs4_file *f)
{
	struct file *ret;

	lockdep_assert_held(&f->fi_lock);

	ret = __nfs4_get_fd(f, O_RDONLY);
	if (!ret)
		ret = __nfs4_get_fd(f, O_RDWR);
	return ret;
}
