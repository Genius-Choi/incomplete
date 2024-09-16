bool pmd_trans_migrating(pmd_t pmd)
{
	struct page *page = pmd_page(pmd);
	return PageLocked(page);
}
