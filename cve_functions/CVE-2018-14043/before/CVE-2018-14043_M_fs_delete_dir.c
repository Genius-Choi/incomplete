static M_fs_error_t M_fs_delete_dir(const char *path)
{
	if (rmdir(path) != 0) {
		return M_fs_error_from_syserr(errno);
	}
	return M_FS_ERROR_SUCCESS;
}
