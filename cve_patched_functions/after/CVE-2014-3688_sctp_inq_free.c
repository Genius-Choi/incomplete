void sctp_inq_free(struct sctp_inq *queue)
{
	struct sctp_chunk *chunk, *tmp;

	/* Empty the queue.  */
	list_for_each_entry_safe(chunk, tmp, &queue->in_chunk_list, list) {
		list_del_init(&chunk->list);
		sctp_chunk_free(chunk);
	}

	/* If there is a packet which is currently being worked on,
	 * free it as well.
	 */
	if (queue->in_progress) {
		sctp_chunk_free(queue->in_progress);
		queue->in_progress = NULL;
	}
}
