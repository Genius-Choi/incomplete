static struct gnttab_copy *xen_netbk_get_requests(struct xen_netbk *netbk,
						  struct xenvif *vif,
						  struct sk_buff *skb,
						  struct xen_netif_tx_request *txp,
						  struct gnttab_copy *gop)
{
	struct skb_shared_info *shinfo = skb_shinfo(skb);
	skb_frag_t *frags = shinfo->frags;
	u16 pending_idx = *((u16 *)skb->data);
	int i, start;

	/* Skip first skb fragment if it is on same page as header fragment. */
	start = (frag_get_pending_idx(&shinfo->frags[0]) == pending_idx);

	for (i = start; i < shinfo->nr_frags; i++, txp++) {
		struct page *page;
		pending_ring_idx_t index;
		struct pending_tx_info *pending_tx_info =
			netbk->pending_tx_info;

		index = pending_index(netbk->pending_cons++);
		pending_idx = netbk->pending_ring[index];
		page = xen_netbk_alloc_page(netbk, skb, pending_idx);
		if (!page)
			return NULL;

		gop->source.u.ref = txp->gref;
		gop->source.domid = vif->domid;
		gop->source.offset = txp->offset;

		gop->dest.u.gmfn = virt_to_mfn(page_address(page));
		gop->dest.domid = DOMID_SELF;
		gop->dest.offset = txp->offset;

		gop->len = txp->size;
		gop->flags = GNTCOPY_source_gref;

		gop++;

		memcpy(&pending_tx_info[pending_idx].req, txp, sizeof(*txp));
		xenvif_get(vif);
		pending_tx_info[pending_idx].vif = vif;
		frag_set_pending_idx(&frags[i], pending_idx);
	}

	return gop;
}
