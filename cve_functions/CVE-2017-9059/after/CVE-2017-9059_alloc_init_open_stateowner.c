alloc_init_open_stateowner(unsigned int strhashval, struct nfsd4_open *open,
			   struct nfsd4_compound_state *cstate)
{
	struct nfs4_client *clp = cstate->clp;
	struct nfs4_openowner *oo, *ret;

	oo = alloc_stateowner(openowner_slab, &open->op_owner, clp);
	if (!oo)
		return NULL;
	oo->oo_owner.so_ops = &openowner_ops;
	oo->oo_owner.so_is_open_owner = 1;
	oo->oo_owner.so_seqid = open->op_seqid;
	oo->oo_flags = 0;
	if (nfsd4_has_session(cstate))
		oo->oo_flags |= NFS4_OO_CONFIRMED;
	oo->oo_time = 0;
	oo->oo_last_closed_stid = NULL;
	INIT_LIST_HEAD(&oo->oo_close_lru);
	spin_lock(&clp->cl_lock);
	ret = find_openstateowner_str_locked(strhashval, open, clp);
	if (ret == NULL) {
		hash_openowner(oo, clp, strhashval);
		ret = oo;
	} else
		nfs4_free_stateowner(&oo->oo_owner);

	spin_unlock(&clp->cl_lock);
	return ret;
}
