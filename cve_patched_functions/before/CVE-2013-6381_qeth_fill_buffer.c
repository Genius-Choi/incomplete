static inline int qeth_fill_buffer(struct qeth_qdio_out_q *queue,
		struct qeth_qdio_out_buffer *buf, struct sk_buff *skb,
		struct qeth_hdr *hdr, int offset, int hd_len)
{
	struct qdio_buffer *buffer;
	int flush_cnt = 0, hdr_len, large_send = 0;

	buffer = buf->buffer;
	atomic_inc(&skb->users);
	skb_queue_tail(&buf->skb_list, skb);

	/*check first on TSO ....*/
	if (hdr->hdr.l3.id == QETH_HEADER_TYPE_TSO) {
		int element = buf->next_element_to_fill;

		hdr_len = sizeof(struct qeth_hdr_tso) +
			((struct qeth_hdr_tso *)hdr)->ext.dg_hdr_len;
		/*fill first buffer entry only with header information */
		buffer->element[element].addr = skb->data;
		buffer->element[element].length = hdr_len;
		buffer->element[element].eflags = SBAL_EFLAGS_FIRST_FRAG;
		buf->next_element_to_fill++;
		skb->data += hdr_len;
		skb->len  -= hdr_len;
		large_send = 1;
	}

	if (offset >= 0) {
		int element = buf->next_element_to_fill;
		buffer->element[element].addr = hdr;
		buffer->element[element].length = sizeof(struct qeth_hdr) +
							hd_len;
		buffer->element[element].eflags = SBAL_EFLAGS_FIRST_FRAG;
		buf->is_header[element] = 1;
		buf->next_element_to_fill++;
	}

	__qeth_fill_buffer(skb, buffer, large_send,
		(int *)&buf->next_element_to_fill, offset);

	if (!queue->do_pack) {
		QETH_CARD_TEXT(queue->card, 6, "fillbfnp");
		/* set state to PRIMED -> will be flushed */
		atomic_set(&buf->state, QETH_QDIO_BUF_PRIMED);
		flush_cnt = 1;
	} else {
		QETH_CARD_TEXT(queue->card, 6, "fillbfpa");
		if (queue->card->options.performance_stats)
			queue->card->perf_stats.skbs_sent_pack++;
		if (buf->next_element_to_fill >=
				QETH_MAX_BUFFER_ELEMENTS(queue->card)) {
			/*
			 * packed buffer if full -> set state PRIMED
			 * -> will be flushed
			 */
			atomic_set(&buf->state, QETH_QDIO_BUF_PRIMED);
			flush_cnt = 1;
		}
	}
	return flush_cnt;
}
