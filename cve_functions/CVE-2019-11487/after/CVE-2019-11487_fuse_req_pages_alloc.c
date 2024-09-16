static struct page **fuse_req_pages_alloc(unsigned int npages, gfp_t flags,
					  struct fuse_page_desc **desc)
{
	struct page **pages;

	pages = kzalloc(npages * (sizeof(struct page *) +
				  sizeof(struct fuse_page_desc)), flags);
	*desc = (void *) pages + npages * sizeof(struct page *);

	return pages;
}
