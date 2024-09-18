M_fs_system_t M_fs_path_get_system_type(M_fs_system_t sys_type)
{
	if (sys_type == M_FS_SYSTEM_AUTO) {
#ifdef _WIN32
		return M_FS_SYSTEM_WINDOWS;
#else
		return M_FS_SYSTEM_UNIX;
#endif
	}
	return sys_type;
}
