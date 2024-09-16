find_writeable_file(struct nfs4_file *f)
{
	struct file *ret;

	spin_lock(&f->fi_lock);
	ret = find_writeable_file_locked(f);
	spin_unlock(&f->fi_lock);

	return ret;
}
