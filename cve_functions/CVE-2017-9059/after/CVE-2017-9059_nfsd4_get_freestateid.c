nfsd4_get_freestateid(struct nfsd4_compound_state *cstate, struct nfsd4_free_stateid *fsp)
{
	get_stateid(cstate, &fsp->fr_stateid);
}
