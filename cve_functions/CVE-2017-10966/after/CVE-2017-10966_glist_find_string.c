GList *glist_find_string(GList *list, const char *key)
{
	for (; list != NULL; list = list->next)
		if (g_strcmp0(list->data, key) == 0) return list;

	return NULL;
}
