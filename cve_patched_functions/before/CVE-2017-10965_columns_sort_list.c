GSList *columns_sort_list(GSList *list, int rows)
{
        GSList *tmp, *sorted;
	int row, skip;

	if (list == NULL || rows == 0)
                return list;

	sorted = NULL;

	for (row = 0; row < rows; row++) {
                tmp = g_slist_nth(list, row);
                skip = 1;
		for (; tmp != NULL; tmp = tmp->next) {
			if (--skip == 0) {
                                skip = rows;
				sorted = g_slist_append(sorted, tmp->data);
			}
		}
	}

	g_return_val_if_fail(g_slist_length(sorted) ==
			     g_slist_length(list), sorted);
        return sorted;
}
