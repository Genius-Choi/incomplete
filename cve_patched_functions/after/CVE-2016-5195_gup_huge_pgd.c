static int gup_huge_pgd(pgd_t orig, pgd_t *pgdp, unsigned long addr,
			unsigned long end, int write,
			struct page **pages, int *nr)
{
	int refs;
	struct page *head, *page;

	if (write && !pgd_write(orig))
		return 0;

	refs = 0;
	head = pgd_page(orig);
	page = head + ((addr & ~PGDIR_MASK) >> PAGE_SHIFT);
	do {
		VM_BUG_ON_PAGE(compound_head(page) != head, page);
		pages[*nr] = page;
		(*nr)++;
		page++;
		refs++;
	} while (addr += PAGE_SIZE, addr != end);

	if (!page_cache_add_speculative(head, refs)) {
		*nr -= refs;
		return 0;
	}

	if (unlikely(pgd_val(orig) != pgd_val(*pgdp))) {
		*nr -= refs;
		while (refs--)
			put_page(head);
		return 0;
	}

	return 1;
}
