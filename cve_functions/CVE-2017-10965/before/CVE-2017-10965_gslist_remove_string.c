GSList *gslist_remove_string (GSList *list, const char *str)
{
	GSList *l;

	l = g_slist_find_custom(list, str, (GCompareFunc) g_strcmp0);
	if (l != NULL)
		return g_slist_remove_link(list, l);

	return list;
}
