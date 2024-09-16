nfsd4_get_readstateid(struct nfsd4_compound_state *cstate, struct nfsd4_read *read)
{
	get_stateid(cstate, &read->rd_stateid);
}
