M_bool M_fs_path_isunc(const char *p)
{
	if (p == NULL) {
		return M_FALSE;
	}

	if (M_str_len(p) >= 2 && p[0] == '\\' && p[1] == '\\') {
		return M_TRUE;
	}

	return M_FALSE;
}
