int nfs_attribute_timeout(struct inode *inode)
{
	struct nfs_inode *nfsi = NFS_I(inode);

	if (nfs_have_delegation(inode, FMODE_READ))
		return 0;
	/*
	 * Special case: if the attribute timeout is set to 0, then always
	 * 		 treat the cache as having expired (unless holding
	 * 		 a delegation).
	 */
	if (nfsi->attrtimeo == 0)
		return 1;
	return !time_in_range(jiffies, nfsi->read_cache_jiffies, nfsi->read_cache_jiffies + nfsi->attrtimeo);
}
