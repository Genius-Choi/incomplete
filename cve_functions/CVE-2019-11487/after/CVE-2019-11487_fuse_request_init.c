static void fuse_request_init(struct fuse_req *req, struct page **pages,
			      struct fuse_page_desc *page_descs,
			      unsigned npages)
{
	INIT_LIST_HEAD(&req->list);
	INIT_LIST_HEAD(&req->intr_entry);
	init_waitqueue_head(&req->waitq);
	refcount_set(&req->count, 1);
	req->pages = pages;
	req->page_descs = page_descs;
	req->max_pages = npages;
	__set_bit(FR_PENDING, &req->flags);
}
