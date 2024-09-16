bool fuse_req_realloc_pages(struct fuse_conn *fc, struct fuse_req *req,
			    gfp_t flags)
{
	struct page **pages;
	struct fuse_page_desc *page_descs;
	unsigned int npages = min_t(unsigned int,
				    max_t(unsigned int, req->max_pages * 2,
					  FUSE_DEFAULT_MAX_PAGES_PER_REQ),
				    fc->max_pages);
	WARN_ON(npages <= req->max_pages);

	pages = fuse_req_pages_alloc(npages, flags, &page_descs);
	if (!pages)
		return false;

	memcpy(pages, req->pages, sizeof(struct page *) * req->max_pages);
	memcpy(page_descs, req->page_descs,
	       sizeof(struct fuse_page_desc) * req->max_pages);
	fuse_req_pages_free(req);
	req->pages = pages;
	req->page_descs = page_descs;
	req->max_pages = npages;

	return true;
}
