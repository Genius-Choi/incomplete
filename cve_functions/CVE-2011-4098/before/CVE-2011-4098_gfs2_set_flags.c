static int gfs2_set_flags(struct file *filp, u32 __user *ptr)
{
	struct inode *inode = filp->f_path.dentry->d_inode;
	u32 fsflags, gfsflags;

	if (get_user(fsflags, ptr))
		return -EFAULT;

	gfsflags = fsflags_cvt(fsflags_to_gfs2, fsflags);
	if (!S_ISDIR(inode->i_mode)) {
		if (gfsflags & GFS2_DIF_INHERIT_JDATA)
			gfsflags ^= (GFS2_DIF_JDATA | GFS2_DIF_INHERIT_JDATA);
		return do_gfs2_set_flags(filp, gfsflags, ~0);
	}
	return do_gfs2_set_flags(filp, gfsflags, ~GFS2_DIF_JDATA);
}
