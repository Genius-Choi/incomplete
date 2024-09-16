static struct page *alloc_fresh_huge_page(struct hstate *h,
		gfp_t gfp_mask, int nid, nodemask_t *nmask)
{
	struct page *page;

	if (hstate_is_gigantic(h))
		page = alloc_gigantic_page(h, gfp_mask, nid, nmask);
	else
		page = alloc_buddy_huge_page(h, gfp_mask,
				nid, nmask);
	if (!page)
		return NULL;

	if (hstate_is_gigantic(h))
		prep_compound_gigantic_page(page, huge_page_order(h));
	prep_new_huge_page(h, page, page_to_nid(page));

	return page;
}
