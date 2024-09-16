nfsd4_set_openstateid(struct nfsd4_compound_state *cstate, struct nfsd4_open *open)
{
	put_stateid(cstate, &open->op_stateid);
}
