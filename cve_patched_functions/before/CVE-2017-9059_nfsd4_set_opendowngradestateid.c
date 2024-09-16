nfsd4_set_opendowngradestateid(struct nfsd4_compound_state *cstate, struct nfsd4_open_downgrade *odp)
{
	put_stateid(cstate, &odp->od_stateid);
}
