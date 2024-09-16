static int gfs2_unstuffer_page(struct gfs2_inode *ip, struct buffer_head *dibh,
			       u64 block, struct page *page)
{
	struct inode *inode = &ip->i_inode;
	struct buffer_head *bh;
	int release = 0;

	if (!page || page->index) {
		page = grab_cache_page(inode->i_mapping, 0);
		if (!page)
			return -ENOMEM;
		release = 1;
	}

	if (!PageUptodate(page)) {
		void *kaddr = kmap(page);
		u64 dsize = i_size_read(inode);
 
		if (dsize > (dibh->b_size - sizeof(struct gfs2_dinode)))
			dsize = dibh->b_size - sizeof(struct gfs2_dinode);

		memcpy(kaddr, dibh->b_data + sizeof(struct gfs2_dinode), dsize);
		memset(kaddr + dsize, 0, PAGE_CACHE_SIZE - dsize);
		kunmap(page);

		SetPageUptodate(page);
	}

	if (!page_has_buffers(page))
		create_empty_buffers(page, 1 << inode->i_blkbits,
				     (1 << BH_Uptodate));

	bh = page_buffers(page);

	if (!buffer_mapped(bh))
		map_bh(bh, inode->i_sb, block);

	set_buffer_uptodate(bh);
	if (!gfs2_is_jdata(ip))
		mark_buffer_dirty(bh);
	if (!gfs2_is_writeback(ip))
		gfs2_trans_add_bh(ip->i_gl, bh, 0);

	if (release) {
		unlock_page(page);
		page_cache_release(page);
	}

	return 0;
}
