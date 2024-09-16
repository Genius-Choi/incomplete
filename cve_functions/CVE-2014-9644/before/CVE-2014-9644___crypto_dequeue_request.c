void *__crypto_dequeue_request(struct crypto_queue *queue, unsigned int offset)
{
	struct list_head *request;

	if (unlikely(!queue->qlen))
		return NULL;

	queue->qlen--;

	if (queue->backlog != &queue->list)
		queue->backlog = queue->backlog->next;

	request = queue->list.next;
	list_del(request);

	return (char *)list_entry(request, struct crypto_async_request, list) -
	       offset;
}
