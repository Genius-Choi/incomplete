static void update_and_free_page(struct hstate *h, struct page *page)
{
	int i;

	VM_BUG_ON(h->order >= MAX_ORDER);

	h->nr_huge_pages--;
	h->nr_huge_pages_node[page_to_nid(page)]--;
	for (i = 0; i < pages_per_huge_page(h); i++) {
		page[i].flags &= ~(1 << PG_locked | 1 << PG_error |
				1 << PG_referenced | 1 << PG_dirty |
				1 << PG_active | 1 << PG_reserved |
				1 << PG_private | 1 << PG_writeback);
	}
	set_compound_page_dtor(page, NULL);
	set_page_refcounted(page);
	arch_release_hugepage(page);
	__free_pages(page, huge_page_order(h));
}
