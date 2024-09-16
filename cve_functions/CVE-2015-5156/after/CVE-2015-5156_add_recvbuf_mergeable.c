static int add_recvbuf_mergeable(struct receive_queue *rq, gfp_t gfp)
{
	struct page_frag *alloc_frag = &rq->alloc_frag;
	char *buf;
	unsigned long ctx;
	int err;
	unsigned int len, hole;

	len = get_mergeable_buf_len(&rq->mrg_avg_pkt_len);
	if (unlikely(!skb_page_frag_refill(len, alloc_frag, gfp)))
		return -ENOMEM;

	buf = (char *)page_address(alloc_frag->page) + alloc_frag->offset;
	ctx = mergeable_buf_to_ctx(buf, len);
	get_page(alloc_frag->page);
	alloc_frag->offset += len;
	hole = alloc_frag->size - alloc_frag->offset;
	if (hole < len) {
		/* To avoid internal fragmentation, if there is very likely not
		 * enough space for another buffer, add the remaining space to
		 * the current buffer. This extra space is not included in
		 * the truesize stored in ctx.
		 */
		len += hole;
		alloc_frag->offset += hole;
	}

	sg_init_one(rq->sg, buf, len);
	err = virtqueue_add_inbuf(rq->vq, rq->sg, 1, (void *)ctx, gfp);
	if (err < 0)
		put_page(virt_to_head_page(buf));

	return err;
}
