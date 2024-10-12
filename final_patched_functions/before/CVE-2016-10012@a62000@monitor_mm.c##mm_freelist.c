mm_freelist(struct mm_master *mmalloc, struct mmtree *head)
{
	struct mm_share *mms, *next;

	for (mms = RB_ROOT(head); mms; mms = next) {
		next = RB_NEXT(mmtree, head, mms);
		RB_REMOVE(mmtree, head, mms);
		if (mmalloc == NULL)
			free(mms);
		else
			mm_free(mmalloc, mms);
	}
}
