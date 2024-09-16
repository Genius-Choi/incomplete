static noinline int btrfs_ioctl_snap_create_transid(struct file *file,
				char *name, unsigned long fd, int subvol,
				u64 *transid, bool readonly,
				struct btrfs_qgroup_inherit **inherit)
{
	int namelen;
	int ret = 0;

	ret = mnt_want_write_file(file);
	if (ret)
		goto out;

	namelen = strlen(name);
	if (strchr(name, '/')) {
		ret = -EINVAL;
		goto out_drop_write;
	}

	if (name[0] == '.' &&
	   (namelen == 1 || (name[1] == '.' && namelen == 2))) {
		ret = -EEXIST;
		goto out_drop_write;
	}

	if (subvol) {
		ret = btrfs_mksubvol(&file->f_path, name, namelen,
				     NULL, transid, readonly, inherit);
	} else {
		struct fd src = fdget(fd);
		struct inode *src_inode;
		if (!src.file) {
			ret = -EINVAL;
			goto out_drop_write;
		}

		src_inode = src.file->f_path.dentry->d_inode;
		if (src_inode->i_sb != file->f_path.dentry->d_inode->i_sb) {
			printk(KERN_INFO "btrfs: Snapshot src from "
			       "another FS\n");
			ret = -EINVAL;
		} else {
			ret = btrfs_mksubvol(&file->f_path, name, namelen,
					     BTRFS_I(src_inode)->root,
					     transid, readonly, inherit);
		}
		fdput(src);
	}
out_drop_write:
	mnt_drop_write_file(file);
out:
	return ret;
}
