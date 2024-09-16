GSList *gslist_find_icase_string(GSList *list, const char *key)
{
	for (; list != NULL; list = list->next)
		if (g_ascii_strcasecmp(list->data, key) == 0) return list;

	return NULL;
}
