int find_substr(const char *list, const char *item)
{
	const char *ptr;

	g_return_val_if_fail(list != NULL, FALSE);
	g_return_val_if_fail(item != NULL, FALSE);

	if (*item == '\0')
		return FALSE;

	for (;;) {
		while (i_isspace(*list)) list++;
		if (*list == '\0') break;

		ptr = strchr(list, ' ');
		if (ptr == NULL) ptr = list+strlen(list);

		if (g_ascii_strncasecmp(list, item, ptr-list) == 0 &&
		    item[ptr-list] == '\0')
			return TRUE;

		list = ptr;
	}

	return FALSE;
}
