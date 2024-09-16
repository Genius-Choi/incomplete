static int fuse_retrieve(struct fuse_conn *fc, struct inode *inode,
			 struct fuse_notify_retrieve_out *outarg)
{
	int err;
	struct address_space *mapping = inode->i_mapping;
	struct fuse_req *req;
	pgoff_t index;
	loff_t file_size;
	unsigned int num;
	unsigned int offset;
	size_t total_len = 0;
	unsigned int num_pages;

	offset = outarg->offset & ~PAGE_MASK;
	file_size = i_size_read(inode);

	num = outarg->size;
	if (outarg->offset > file_size)
		num = 0;
	else if (outarg->offset + num > file_size)
		num = file_size - outarg->offset;

	num_pages = (num + offset + PAGE_SIZE - 1) >> PAGE_SHIFT;
	num_pages = min(num_pages, fc->max_pages);

	req = fuse_get_req(fc, num_pages);
	if (IS_ERR(req))
		return PTR_ERR(req);

	req->in.h.opcode = FUSE_NOTIFY_REPLY;
	req->in.h.nodeid = outarg->nodeid;
	req->in.numargs = 2;
	req->in.argpages = 1;
	req->end = fuse_retrieve_end;

	index = outarg->offset >> PAGE_SHIFT;

	while (num && req->num_pages < num_pages) {
		struct page *page;
		unsigned int this_num;

		page = find_get_page(mapping, index);
		if (!page)
			break;

		this_num = min_t(unsigned, num, PAGE_SIZE - offset);
		req->pages[req->num_pages] = page;
		req->page_descs[req->num_pages].offset = offset;
		req->page_descs[req->num_pages].length = this_num;
		req->num_pages++;

		offset = 0;
		num -= this_num;
		total_len += this_num;
		index++;
	}
	req->misc.retrieve_in.offset = outarg->offset;
	req->misc.retrieve_in.size = total_len;
	req->in.args[0].size = sizeof(req->misc.retrieve_in);
	req->in.args[0].value = &req->misc.retrieve_in;
	req->in.args[1].size = total_len;

	err = fuse_request_send_notify_reply(fc, req, outarg->notify_unique);
	if (err) {
		fuse_retrieve_end(fc, req);
		fuse_put_request(fc, req);
	}

	return err;
}
