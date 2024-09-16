char *gslist_to_string(GSList *list, const char *delimiter)
{
	GString *str;
	char *ret;

	str = g_string_new(NULL);
	while (list != NULL) {
		if (str->len != 0) g_string_append(str, delimiter);
		g_string_append(str, list->data);

		list = list->next;
	}

        ret = str->str;
	g_string_free(str, FALSE);
	return ret;
}
