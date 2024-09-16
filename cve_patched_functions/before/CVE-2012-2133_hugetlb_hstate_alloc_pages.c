static void __init hugetlb_hstate_alloc_pages(struct hstate *h)
{
	unsigned long i;

	for (i = 0; i < h->max_huge_pages; ++i) {
		if (h->order >= MAX_ORDER) {
			if (!alloc_bootmem_huge_page(h))
				break;
		} else if (!alloc_fresh_huge_page(h,
					 &node_states[N_HIGH_MEMORY]))
			break;
	}
	h->max_huge_pages = i;
}
