void page_put_link(struct inode *unused, void *cookie)
{
	struct page *page = cookie;
	kunmap(page);
	page_cache_release(page);
}
