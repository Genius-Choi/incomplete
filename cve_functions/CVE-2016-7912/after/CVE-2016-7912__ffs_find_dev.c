static struct ffs_dev *_ffs_find_dev(const char *name)
{
	struct ffs_dev *dev;

	dev = _ffs_get_single_dev();
	if (dev)
		return dev;

	return _ffs_do_find_dev(name);
}
