static int gfs2_readdir(struct file *file, void *dirent, filldir_t filldir)
{
	struct inode *dir = file->f_mapping->host;
	struct gfs2_inode *dip = GFS2_I(dir);
	struct gfs2_holder d_gh;
	u64 offset = file->f_pos;
	int error;

	gfs2_holder_init(dip->i_gl, LM_ST_SHARED, 0, &d_gh);
	error = gfs2_glock_nq(&d_gh);
	if (error) {
		gfs2_holder_uninit(&d_gh);
		return error;
	}

	error = gfs2_dir_read(dir, &offset, dirent, filldir);

	gfs2_glock_dq_uninit(&d_gh);

	file->f_pos = offset;

	return error;
}
