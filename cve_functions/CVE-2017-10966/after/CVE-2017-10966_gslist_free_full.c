void gslist_free_full (GSList *list, GDestroyNotify free_func)
{
	GSList *tmp;

	if (list == NULL)
		return;

	for (tmp = list; tmp != NULL; tmp = tmp->next)
		free_func(tmp->data);

	g_slist_free(list);
}
