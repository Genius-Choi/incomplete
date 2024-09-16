xfs_file_aio_write_checks(
	struct file		*file,
	loff_t			*pos,
	size_t			*count,
	int			*iolock)
{
	struct inode		*inode = file->f_mapping->host;
	struct xfs_inode	*ip = XFS_I(inode);
	int			error = 0;

restart:
	error = generic_write_checks(file, pos, count, S_ISBLK(inode->i_mode));
	if (error)
		return error;

	/*
	 * If the offset is beyond the size of the file, we need to zero any
	 * blocks that fall between the existing EOF and the start of this
	 * write.  If zeroing is needed and we are currently holding the
	 * iolock shared, we need to update it to exclusive which implies
	 * having to redo all checks before.
	 */
	if (*pos > i_size_read(inode)) {
		if (*iolock == XFS_IOLOCK_SHARED) {
			xfs_rw_iunlock(ip, *iolock);
			*iolock = XFS_IOLOCK_EXCL;
			xfs_rw_ilock(ip, *iolock);
			goto restart;
		}
		error = -xfs_zero_eof(ip, *pos, i_size_read(inode));
		if (error)
			return error;
	}

	/*
	 * Updating the timestamps will grab the ilock again from
	 * xfs_fs_dirty_inode, so we have to call it after dropping the
	 * lock above.  Eventually we should look into a way to avoid
	 * the pointless lock roundtrip.
	 */
	if (likely(!(file->f_mode & FMODE_NOCMTIME))) {
		error = file_update_time(file);
		if (error)
			return error;
	}

	/*
	 * If we're writing the file then make sure to clear the setuid and
	 * setgid bits if the process is not being run by root.  This keeps
	 * people from modifying setuid and setgid binaries.
	 */
	return file_remove_suid(file);
}
