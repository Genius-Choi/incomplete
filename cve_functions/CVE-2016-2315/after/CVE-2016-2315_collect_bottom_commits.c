static struct commit_list *collect_bottom_commits(struct commit_list *list)
{
	struct commit_list *elem, *bottom = NULL;
	for (elem = list; elem; elem = elem->next)
		if (elem->item->object.flags & BOTTOM)
			commit_list_insert(elem->item, &bottom);
	return bottom;
}
