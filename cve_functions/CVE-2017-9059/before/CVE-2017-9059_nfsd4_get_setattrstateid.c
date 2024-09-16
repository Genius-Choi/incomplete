nfsd4_get_setattrstateid(struct nfsd4_compound_state *cstate, struct nfsd4_setattr *setattr)
{
	get_stateid(cstate, &setattr->sa_stateid);
}
