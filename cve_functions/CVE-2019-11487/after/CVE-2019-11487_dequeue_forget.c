static struct fuse_forget_link *dequeue_forget(struct fuse_iqueue *fiq,
					       unsigned max,
					       unsigned *countp)
{
	struct fuse_forget_link *head = fiq->forget_list_head.next;
	struct fuse_forget_link **newhead = &head;
	unsigned count;

	for (count = 0; *newhead != NULL && count < max; count++)
		newhead = &(*newhead)->next;

	fiq->forget_list_head.next = *newhead;
	*newhead = NULL;
	if (fiq->forget_list_head.next == NULL)
		fiq->forget_list_tail = &fiq->forget_list_head;

	if (countp != NULL)
		*countp = count;

	return head;
}
