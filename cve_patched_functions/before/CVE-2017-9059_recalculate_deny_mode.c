recalculate_deny_mode(struct nfs4_file *fp)
{
	struct nfs4_ol_stateid *stp;

	spin_lock(&fp->fi_lock);
	fp->fi_share_deny = 0;
	list_for_each_entry(stp, &fp->fi_stateids, st_perfile)
		fp->fi_share_deny |= bmap_to_share_mode(stp->st_deny_bmap);
	spin_unlock(&fp->fi_lock);
}
