unsigned long hugetlb_total_pages(void)
{
	struct hstate *h = &default_hstate;
	return h->nr_huge_pages * pages_per_huge_page(h);
}
