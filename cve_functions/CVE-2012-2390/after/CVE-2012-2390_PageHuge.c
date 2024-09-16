int PageHuge(struct page *page)
{
	compound_page_dtor *dtor;

	if (!PageCompound(page))
		return 0;

	page = compound_head(page);
	dtor = get_compound_page_dtor(page);

	return dtor == free_huge_page;
}
