int rewrite_data_page(struct f2fs_io_info *fio)
{
	fio->new_blkaddr = fio->old_blkaddr;
	stat_inc_inplace_blocks(fio->sbi);
	return f2fs_submit_page_bio(fio);
}
