nfsd4_set_closestateid(struct nfsd4_compound_state *cstate, struct nfsd4_close *close)
{
	put_stateid(cstate, &close->cl_stateid);
}
