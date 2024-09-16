find_any_file(struct nfs4_file *f)
{
	struct file *ret;

	spin_lock(&f->fi_lock);
	ret = __nfs4_get_fd(f, O_RDWR);
	if (!ret) {
		ret = __nfs4_get_fd(f, O_WRONLY);
		if (!ret)
			ret = __nfs4_get_fd(f, O_RDONLY);
	}
	spin_unlock(&f->fi_lock);
	return ret;
}
