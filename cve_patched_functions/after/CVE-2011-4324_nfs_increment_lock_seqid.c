void nfs_increment_lock_seqid(int status, struct nfs_seqid *seqid)
{
	nfs_increment_seqid(status, seqid);
}
