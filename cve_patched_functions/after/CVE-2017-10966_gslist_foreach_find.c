void *gslist_foreach_find(GSList *list, FOREACH_FIND_FUNC func, const void *data)
{
	void *ret;

	while (list != NULL) {
		ret = func(list->data, (void *) data);
                if (ret != NULL) return ret;

		list = list->next;
	}

	return NULL;
}
