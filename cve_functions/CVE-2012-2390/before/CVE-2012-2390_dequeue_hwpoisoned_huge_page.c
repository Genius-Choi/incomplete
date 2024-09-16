int dequeue_hwpoisoned_huge_page(struct page *hpage)
{
	struct hstate *h = page_hstate(hpage);
	int nid = page_to_nid(hpage);
	int ret = -EBUSY;

	spin_lock(&hugetlb_lock);
	if (is_hugepage_on_freelist(hpage)) {
		list_del(&hpage->lru);
		set_page_refcounted(hpage);
		h->free_huge_pages--;
		h->free_huge_pages_node[nid]--;
		ret = 0;
	}
	spin_unlock(&hugetlb_lock);
	return ret;
}
