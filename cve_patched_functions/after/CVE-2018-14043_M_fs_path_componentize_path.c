M_list_str_t *M_fs_path_componentize_path(const char *path, M_fs_system_t sys_type)
{
	M_list_str_t *list1;
	M_list_str_t *list2;
	M_list_str_t *list3;
	const char   *const_temp;
	const char   *const_temp2;
	size_t len;
	size_t len2;
	size_t i;
	size_t j;

	sys_type = M_fs_path_get_system_type(sys_type);

	list1 = M_list_str_split('/', path, M_LIST_STR_NONE, M_FALSE);
	list3 = M_list_str_create(M_LIST_STR_NONE);
	len = M_list_str_len(list1);
	for (i=0; i<len; i++) {
		const_temp = M_list_str_at(list1, i);
		if (const_temp == NULL || *const_temp == '\0') {
			continue;
		}
		list2 = M_list_str_split('\\', const_temp, M_LIST_STR_NONE, M_FALSE);
		len2 = M_list_str_len(list2);
		for (j=0; j<len2; j++) {
			const_temp2 = M_list_str_at(list2, j);
			if (const_temp2 == NULL || *const_temp2 == '\0') {
				continue;
			}
			M_list_str_insert(list3, const_temp2);
		}
		M_list_str_destroy(list2);
	}
	M_list_str_destroy(list1);

	if ((sys_type == M_FS_SYSTEM_UNIX && M_fs_path_isabs(path, sys_type)) ||
		(sys_type == M_FS_SYSTEM_WINDOWS && M_fs_path_isunc(path)))
	{
		M_list_str_insert_at(list3, "", 0);
	}

	return list3;
}
