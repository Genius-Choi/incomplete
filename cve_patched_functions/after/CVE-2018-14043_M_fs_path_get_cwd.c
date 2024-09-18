M_fs_error_t M_fs_path_get_cwd(char **cwd)
{
	char   *temp;
	size_t  path_max;
#ifdef _WIN32
	DWORD   dpath_max;
#endif

	if (cwd == NULL)
		return M_FS_ERROR_INVALID;
	*cwd = NULL;

	path_max = M_fs_path_get_path_max(M_FS_SYSTEM_AUTO)+1;
	temp     = M_malloc(path_max);

#ifdef _WIN32
	if (!M_win32_size_t_to_dword(path_max, &dpath_max))
		return M_FS_ERROR_INVALID;
	if (GetCurrentDirectory(dpath_max, temp) == 0) {
		M_free(temp);
		return M_fs_error_from_syserr(GetLastError());
	}
#else
	if (getcwd(temp, path_max) == NULL) {
		M_free(temp);
		return M_fs_error_from_syserr(errno);
	}
#endif

	*cwd = M_strdup(temp);
	M_free(temp);
	return M_FS_ERROR_SUCCESS;
}
