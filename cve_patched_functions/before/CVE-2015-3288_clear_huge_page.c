void clear_huge_page(struct page *page,
		     unsigned long addr, unsigned int pages_per_huge_page)
{
	int i;

	if (unlikely(pages_per_huge_page > MAX_ORDER_NR_PAGES)) {
		clear_gigantic_page(page, addr, pages_per_huge_page);
		return;
	}

	might_sleep();
	for (i = 0; i < pages_per_huge_page; i++) {
		cond_resched();
		clear_user_highpage(page + i, addr + i * PAGE_SIZE);
	}
}
