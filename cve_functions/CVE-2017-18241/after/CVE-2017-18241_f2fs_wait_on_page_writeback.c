void f2fs_wait_on_page_writeback(struct page *page,
				enum page_type type, bool ordered)
{
	if (PageWriteback(page)) {
		struct f2fs_sb_info *sbi = F2FS_P_SB(page);

		f2fs_submit_merged_write_cond(sbi, page->mapping->host,
						0, page->index, type);
		if (ordered)
			wait_on_page_writeback(page);
		else
			wait_for_stable_page(page);
	}
}
