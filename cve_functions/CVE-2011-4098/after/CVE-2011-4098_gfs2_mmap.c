static int gfs2_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct gfs2_inode *ip = GFS2_I(file->f_mapping->host);

	if (!(file->f_flags & O_NOATIME) &&
	    !IS_NOATIME(&ip->i_inode)) {
		struct gfs2_holder i_gh;
		int error;

		gfs2_holder_init(ip->i_gl, LM_ST_SHARED, LM_FLAG_ANY, &i_gh);
		error = gfs2_glock_nq(&i_gh);
		if (error == 0) {
			file_accessed(file);
			gfs2_glock_dq(&i_gh);
		}
		gfs2_holder_uninit(&i_gh);
		if (error)
			return error;
	}
	vma->vm_ops = &gfs2_vm_ops;
	vma->vm_flags |= VM_CAN_NONLINEAR;

	return 0;
}
