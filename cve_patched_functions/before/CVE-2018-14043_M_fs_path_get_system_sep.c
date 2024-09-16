char M_fs_path_get_system_sep(M_fs_system_t sys_type)
{
	if (M_fs_path_get_system_type(sys_type) == M_FS_SYSTEM_WINDOWS) {
		return M_fs_path_sep_win;
	}
	return M_fs_path_sep_unix;
}
