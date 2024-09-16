nfs4_get_stateowner(struct nfs4_stateowner *sop)
{
	atomic_inc(&sop->so_count);
	return sop;
}
