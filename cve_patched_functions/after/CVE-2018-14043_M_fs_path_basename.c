char *M_fs_path_basename(const char *path, M_fs_system_t sys_type)
{
	char *out;

	M_fs_path_split(path, NULL, &out, sys_type);
	return out;
}
