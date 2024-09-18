unsigned int xen_netbk_count_skb_slots(struct xenvif *vif, struct sk_buff *skb)
{
	unsigned int count;
	int i, copy_off;

	count = DIV_ROUND_UP(skb_headlen(skb), PAGE_SIZE);

	copy_off = skb_headlen(skb) % PAGE_SIZE;

	if (skb_shinfo(skb)->gso_size)
		count++;

	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		unsigned long size = skb_frag_size(&skb_shinfo(skb)->frags[i]);
		unsigned long offset = skb_shinfo(skb)->frags[i].page_offset;
		unsigned long bytes;

		offset &= ~PAGE_MASK;

		while (size > 0) {
			BUG_ON(offset >= PAGE_SIZE);
			BUG_ON(copy_off > MAX_BUFFER_OFFSET);

			bytes = PAGE_SIZE - offset;

			if (bytes > size)
				bytes = size;

			if (start_new_rx_buffer(copy_off, bytes, 0)) {
				count++;
				copy_off = 0;
			}

			if (copy_off + bytes > MAX_BUFFER_OFFSET)
				bytes = MAX_BUFFER_OFFSET - copy_off;

			copy_off += bytes;

			offset += bytes;
			size -= bytes;

			if (offset == PAGE_SIZE)
				offset = 0;
		}
	}
	return count;
}
