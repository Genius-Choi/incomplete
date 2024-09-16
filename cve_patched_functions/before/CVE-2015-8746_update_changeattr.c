static void update_changeattr(struct inode *dir, struct nfs4_change_info *cinfo)
{
	struct nfs_inode *nfsi = NFS_I(dir);

	spin_lock(&dir->i_lock);
	nfsi->cache_validity |= NFS_INO_INVALID_ATTR|NFS_INO_INVALID_DATA;
	if (!cinfo->atomic || cinfo->before != dir->i_version)
		nfs_force_lookup_revalidate(dir);
	dir->i_version = cinfo->after;
	nfsi->attr_gencount = nfs_inc_attr_generation_counter();
	nfs_fscache_invalidate(dir);
	spin_unlock(&dir->i_lock);
}
