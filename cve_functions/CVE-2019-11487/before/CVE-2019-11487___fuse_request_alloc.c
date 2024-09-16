static struct fuse_req *__fuse_request_alloc(unsigned npages, gfp_t flags)
{
	struct fuse_req *req = kmem_cache_zalloc(fuse_req_cachep, flags);
	if (req) {
		struct page **pages = NULL;
		struct fuse_page_desc *page_descs = NULL;

		WARN_ON(npages > FUSE_MAX_MAX_PAGES);
		if (npages > FUSE_REQ_INLINE_PAGES) {
			pages = fuse_req_pages_alloc(npages, flags,
						     &page_descs);
			if (!pages) {
				kmem_cache_free(fuse_req_cachep, req);
				return NULL;
			}
		} else if (npages) {
			pages = req->inline_pages;
			page_descs = req->inline_page_descs;
		}

		fuse_request_init(req, pages, page_descs, npages);
	}
	return req;
}
