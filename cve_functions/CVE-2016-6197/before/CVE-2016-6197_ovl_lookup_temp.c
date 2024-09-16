struct dentry *ovl_lookup_temp(struct dentry *workdir, struct dentry *dentry)
{
	struct dentry *temp;
	char name[20];

	snprintf(name, sizeof(name), "#%lx", (unsigned long) dentry);

	temp = lookup_one_len(name, workdir, strlen(name));
	if (!IS_ERR(temp) && temp->d_inode) {
		pr_err("overlayfs: workdir/%s already exists\n", name);
		dput(temp);
		temp = ERR_PTR(-EIO);
	}

	return temp;
}
