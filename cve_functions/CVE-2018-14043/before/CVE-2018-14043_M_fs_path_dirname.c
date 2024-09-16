char *M_fs_path_dirname(const char *path, M_fs_system_t sys_type)
{
	char *out;

	M_fs_path_split(path, &out, NULL, sys_type);
	return out;
}
