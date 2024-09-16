static int is_hugepage_on_freelist(struct page *hpage)
{
	struct page *page;
	struct page *tmp;
	struct hstate *h = page_hstate(hpage);
	int nid = page_to_nid(hpage);

	list_for_each_entry_safe(page, tmp, &h->hugepage_freelists[nid], lru)
		if (page == hpage)
			return 1;
	return 0;
}
