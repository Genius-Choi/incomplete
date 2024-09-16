static int lookup_node(unsigned long addr)
{
	struct page *p;
	int err;

	err = get_user_pages(addr & PAGE_MASK, 1, 0, &p, NULL);
	if (err >= 0) {
		err = page_to_nid(p);
		put_page(p);
	}
	return err;
}
