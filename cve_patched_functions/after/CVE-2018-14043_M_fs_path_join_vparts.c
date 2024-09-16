char *M_fs_path_join_vparts(M_fs_system_t sys_type, size_t num, ...)
{
	M_list_str_t *parts;
	char         *out;
	va_list       ap;
	size_t        i;

	parts = M_list_str_create(M_LIST_STR_NONE);
	va_start(ap, num);
	for (i=0; i<num; i++) {
		M_list_str_insert(parts, va_arg(ap, const char *));
	}
	va_end(ap);

	out = M_fs_path_join_parts(parts, sys_type);
	M_list_str_destroy(parts);
	return out;
}
