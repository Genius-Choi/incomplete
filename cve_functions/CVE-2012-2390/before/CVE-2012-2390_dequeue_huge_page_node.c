static struct page *dequeue_huge_page_node(struct hstate *h, int nid)
{
	struct page *page;

	if (list_empty(&h->hugepage_freelists[nid]))
		return NULL;
	page = list_entry(h->hugepage_freelists[nid].next, struct page, lru);
	list_del(&page->lru);
	set_page_refcounted(page);
	h->free_huge_pages--;
	h->free_huge_pages_node[nid]--;
	return page;
}
