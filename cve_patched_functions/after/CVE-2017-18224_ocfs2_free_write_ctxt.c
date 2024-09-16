static void ocfs2_free_write_ctxt(struct inode *inode,
				  struct ocfs2_write_ctxt *wc)
{
	ocfs2_free_unwritten_list(inode, &wc->w_unwritten_list);
	ocfs2_unlock_pages(wc);
	brelse(wc->w_di_bh);
	kfree(wc);
}
