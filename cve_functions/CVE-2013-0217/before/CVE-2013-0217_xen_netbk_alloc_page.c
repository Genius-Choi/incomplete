static struct page *xen_netbk_alloc_page(struct xen_netbk *netbk,
					 struct sk_buff *skb,
					 u16 pending_idx)
{
	struct page *page;
	page = alloc_page(GFP_KERNEL|__GFP_COLD);
	if (!page)
		return NULL;
	set_page_ext(page, netbk, pending_idx);
	netbk->mmap_pages[pending_idx] = page;
	return page;
}
