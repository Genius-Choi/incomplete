GList *glist_find_icase_string(GList *list, const char *key)
{
	for (; list != NULL; list = list->next)
		if (g_ascii_strcasecmp(list->data, key) == 0) return list;

	return NULL;
}
