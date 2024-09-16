static void M_fs_path_split(const char *path, char **dir, char **name, M_fs_system_t sys_type)
{
	M_list_str_t *parts;
	char         *temp;

	if (dir == NULL && name == NULL)
		return;

	if (dir != NULL)
		*dir = NULL;
	if (name != NULL)
		*name = NULL;

	if (path == NULL || *path == '\0') {
		if (dir != NULL) {
			*dir = M_strdup(".");
		}
		return;
	}

	sys_type = M_fs_path_get_system_type(sys_type);
	parts    = M_fs_path_componentize_path(path, sys_type);
	temp     = M_list_str_take_at(parts, M_list_str_len(parts)-1);

	if (M_list_str_len(parts) == 0 && M_fs_path_isabs(path, sys_type)) {
		M_list_str_insert(parts, temp);
		M_free(temp);
		temp = NULL;
	}

	if (temp != NULL && *temp == '\0') {
		M_free(temp);
		temp = NULL;
	}

	if (name != NULL) {
		*name = temp;
	} else {
		M_free(temp);
	}

	if (dir != NULL) {
		*dir = M_fs_path_join_parts(parts, sys_type);
		if (*dir == NULL) {
			*dir = M_strdup(".");
		}
	}

	M_list_str_destroy(parts);
}
