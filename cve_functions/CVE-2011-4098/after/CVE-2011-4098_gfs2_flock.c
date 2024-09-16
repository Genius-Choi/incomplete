static int gfs2_flock(struct file *file, int cmd, struct file_lock *fl)
{
	if (!(fl->fl_flags & FL_FLOCK))
		return -ENOLCK;
	if (fl->fl_type & LOCK_MAND)
		return -EOPNOTSUPP;

	if (fl->fl_type == F_UNLCK) {
		do_unflock(file, fl);
		return 0;
	} else {
		return do_flock(file, cmd, fl);
	}
}
