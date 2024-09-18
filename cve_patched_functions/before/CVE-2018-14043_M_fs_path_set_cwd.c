M_fs_error_t M_fs_path_set_cwd(const char *path)
{
	if (path == NULL || *path == '\0')
		return M_FS_ERROR_INVALID;

#ifdef _WIN32
	if (SetCurrentDirectory(path) == 0) {
		return M_fs_error_from_syserr(GetLastError());
	}
#else
	if (chdir(path) != 0) {
		return M_fs_error_from_syserr(errno);
	}
#endif

	return M_FS_ERROR_SUCCESS;
}
