M_bool M_fs_path_isabs(const char *p, M_fs_system_t sys_type)
{
	size_t len;

	if (p == NULL) {
		return M_FALSE;
	}

	len = M_str_len(p);
	if (len == 0) {
		return M_FALSE;
	}

	sys_type = M_fs_path_get_system_type(sys_type);
	if ((sys_type == M_FS_SYSTEM_WINDOWS && (M_fs_path_isunc(p) ||
			(len >= 2 && (p[1] == ':' || (p[0] == '\\' && p[1] == '\\'))))) ||
		(sys_type == M_FS_SYSTEM_UNIX && *p == '/'))
	{
		return M_TRUE;
	}

	return M_FALSE;
}
