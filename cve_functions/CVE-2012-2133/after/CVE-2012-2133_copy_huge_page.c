void copy_huge_page(struct page *dst, struct page *src)
{
	int i;
	struct hstate *h = page_hstate(src);

	if (unlikely(pages_per_huge_page(h) > MAX_ORDER_NR_PAGES)) {
		copy_gigantic_page(dst, src);
		return;
	}

	might_sleep();
	for (i = 0; i < pages_per_huge_page(h); i++) {
		cond_resched();
		copy_highpage(dst + i, src + i);
	}
}
