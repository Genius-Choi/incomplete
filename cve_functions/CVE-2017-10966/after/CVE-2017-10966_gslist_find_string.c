GSList *gslist_find_string(GSList *list, const char *key)
{
	for (; list != NULL; list = list->next)
		if (g_strcmp0(list->data, key) == 0) return list;

	return NULL;
}
