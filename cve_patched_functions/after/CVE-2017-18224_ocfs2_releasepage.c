static int ocfs2_releasepage(struct page *page, gfp_t wait)
{
	if (!page_has_buffers(page))
		return 0;
	return try_to_free_buffers(page);
}
