static void nfs4_layoutreturn_release(void *calldata)
{
	struct nfs4_layoutreturn *lrp = calldata;
	struct pnfs_layout_hdr *lo = lrp->args.layout;
	LIST_HEAD(freeme);

	dprintk("--> %s\n", __func__);
	spin_lock(&lo->plh_inode->i_lock);
	if (lrp->res.lrs_present)
		pnfs_set_layout_stateid(lo, &lrp->res.stateid, true);
	pnfs_mark_matching_lsegs_invalid(lo, &freeme, &lrp->args.range);
	pnfs_clear_layoutreturn_waitbit(lo);
	lo->plh_block_lgets--;
	spin_unlock(&lo->plh_inode->i_lock);
	pnfs_free_lseg_list(&freeme);
	pnfs_put_layout_hdr(lrp->args.layout);
	nfs_iput_and_deactive(lrp->inode);
	kfree(calldata);
	dprintk("<-- %s\n", __func__);
}
