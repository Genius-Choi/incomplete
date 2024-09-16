void update_meta_page(struct f2fs_sb_info *sbi, void *src, block_t blk_addr)
{
	struct page *page = grab_meta_page(sbi, blk_addr);
	void *dst = page_address(page);

	if (src)
		memcpy(dst, src, PAGE_SIZE);
	else
		memset(dst, 0, PAGE_SIZE);
	set_page_dirty(page);
	f2fs_put_page(page, 1);
}
