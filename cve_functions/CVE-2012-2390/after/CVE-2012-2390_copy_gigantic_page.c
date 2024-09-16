static void copy_gigantic_page(struct page *dst, struct page *src)
{
	int i;
	struct hstate *h = page_hstate(src);
	struct page *dst_base = dst;
	struct page *src_base = src;

	for (i = 0; i < pages_per_huge_page(h); ) {
		cond_resched();
		copy_highpage(dst, src);

		i++;
		dst = mem_map_next(dst, dst_base, i);
		src = mem_map_next(src, src_base, i);
	}
}
