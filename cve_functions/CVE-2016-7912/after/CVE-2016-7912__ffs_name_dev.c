static int _ffs_name_dev(struct ffs_dev *dev, const char *name)
{
	struct ffs_dev *existing;

	existing = _ffs_do_find_dev(name);
	if (existing)
		return -EBUSY;

	dev->name = name;

	return 0;
}
