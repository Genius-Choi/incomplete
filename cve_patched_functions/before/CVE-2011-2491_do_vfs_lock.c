static int do_vfs_lock(struct file_lock *fl)
{
	int res = 0;
	switch (fl->fl_flags & (FL_POSIX|FL_FLOCK)) {
		case FL_POSIX:
			res = posix_lock_file_wait(fl->fl_file, fl);
			break;
		case FL_FLOCK:
			res = flock_lock_file_wait(fl->fl_file, fl);
			break;
		default:
			BUG();
	}
	return res;
}
