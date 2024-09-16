char *gslistptr_to_string(GSList *list, int offset, const char *delimiter)
{
	GString *str;
	char **data, *ret;

	str = g_string_new(NULL);
	while (list != NULL) {
		data = G_STRUCT_MEMBER_P(list->data, offset);

		if (str->len != 0) g_string_append(str, delimiter);
		g_string_append(str, *data);
		list = list->next;
	}

        ret = str->str;
	g_string_free(str, FALSE);
	return ret;
}
