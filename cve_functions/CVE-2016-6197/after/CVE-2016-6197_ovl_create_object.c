static int ovl_create_object(struct dentry *dentry, int mode, dev_t rdev,
			     const char *link)
{
	int err;

	err = ovl_want_write(dentry);
	if (!err) {
		err = ovl_create_or_link(dentry, mode, rdev, link, NULL);
		ovl_drop_write(dentry);
	}

	return err;
}
