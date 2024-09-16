int strarray_find(char **array, const char *item)
{
	char **tmp;
	int index;

	g_return_val_if_fail(array != NULL, -1);
	g_return_val_if_fail(item != NULL, -1);

	index = 0;
	for (tmp = array; *tmp != NULL; tmp++, index++) {
		if (g_ascii_strcasecmp(*tmp, item) == 0)
			return index;
	}

	return -1;
}
