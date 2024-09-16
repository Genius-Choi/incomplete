static struct fwnet_partial_datagram *fwnet_pd_new(struct net_device *net,
		struct fwnet_peer *peer, u16 datagram_label, unsigned dg_size,
		void *frag_buf, unsigned frag_off, unsigned frag_len)
{
	struct fwnet_partial_datagram *new;
	struct fwnet_fragment_info *fi;

	new = kmalloc(sizeof(*new), GFP_ATOMIC);
	if (!new)
		goto fail;

	INIT_LIST_HEAD(&new->fi_list);
	fi = fwnet_frag_new(new, frag_off, frag_len);
	if (fi == NULL)
		goto fail_w_new;

	new->datagram_label = datagram_label;
	new->datagram_size = dg_size;
	new->skb = dev_alloc_skb(dg_size + LL_RESERVED_SPACE(net));
	if (new->skb == NULL)
		goto fail_w_fi;

	skb_reserve(new->skb, LL_RESERVED_SPACE(net));
	new->pbuf = skb_put(new->skb, dg_size);
	memcpy(new->pbuf + frag_off, frag_buf, frag_len);
	list_add_tail(&new->pd_link, &peer->pd_list);

	return new;

fail_w_fi:
	kfree(fi);
fail_w_new:
	kfree(new);
fail:
	return NULL;
}
