static void nfs4_delegreturn_release(void *calldata)
{
	struct nfs4_delegreturndata *data = calldata;
	struct inode *inode = data->inode;

	if (inode) {
		if (data->roc)
			pnfs_roc_release(inode);
		nfs_iput_and_deactive(inode);
	}
	kfree(calldata);
}
