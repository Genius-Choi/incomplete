mlist_free(struct mlist *mlist)
{
	struct mlist *ml, *next;

	if (mlist == NULL)
		return;

	ml = mlist->next;
	for (ml = mlist->next; (next = ml->next) != NULL; ml = next) {
		if (ml->map)
			apprentice_unmap(ml->map);
		free(ml);
		if (ml == mlist)
			break;
	}
}
