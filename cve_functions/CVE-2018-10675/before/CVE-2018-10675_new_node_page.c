static struct page *new_node_page(struct page *page, unsigned long node, int **x)
{
	if (PageHuge(page))
		return alloc_huge_page_node(page_hstate(compound_head(page)),
					node);
	else
		return __alloc_pages_node(node, GFP_HIGHUSER_MOVABLE |
						    __GFP_THISNODE, 0);
}
