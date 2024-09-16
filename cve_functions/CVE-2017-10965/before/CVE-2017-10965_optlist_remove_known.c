GList *optlist_remove_known(const char *cmd, GHashTable *optlist)
{
	GList *list, *tmp, *next;

	list = g_hash_table_get_keys(optlist);
	if (cmd != NULL && list != NULL) {
		for (tmp = list; tmp != NULL; tmp = next) {
			char *option = tmp->data;
			next = tmp->next;

			if (command_have_option(cmd, option))
				list = g_list_remove(list, option);
		}
	}

	return list;
}
