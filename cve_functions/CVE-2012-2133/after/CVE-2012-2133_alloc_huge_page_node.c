struct page *alloc_huge_page_node(struct hstate *h, int nid)
{
	struct page *page;

	spin_lock(&hugetlb_lock);
	page = dequeue_huge_page_node(h, nid);
	spin_unlock(&hugetlb_lock);

	if (!page)
		page = alloc_buddy_huge_page(h, nid);

	return page;
}
