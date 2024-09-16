static struct page *new_page_node(struct page *p, unsigned long private,
		int **result)
{
	struct page_to_node *pm = (struct page_to_node *)private;

	while (pm->node != MAX_NUMNODES && pm->page != p)
		pm++;

	if (pm->node == MAX_NUMNODES)
		return NULL;

	*result = &pm->status;

	if (PageHuge(p))
		return alloc_huge_page_node(page_hstate(compound_head(p)),
					pm->node);
	else
		return __alloc_pages_node(pm->node,
				GFP_HIGHUSER_MOVABLE | __GFP_THISNODE, 0);
}
