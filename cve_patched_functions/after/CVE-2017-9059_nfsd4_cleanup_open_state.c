void nfsd4_cleanup_open_state(struct nfsd4_compound_state *cstate,
			      struct nfsd4_open *open)
{
	if (open->op_openowner) {
		struct nfs4_stateowner *so = &open->op_openowner->oo_owner;

		nfsd4_cstate_assign_replay(cstate, so);
		nfs4_put_stateowner(so);
	}
	if (open->op_file)
		kmem_cache_free(file_slab, open->op_file);
	if (open->op_stp)
		nfs4_put_stid(&open->op_stp->st_stid);
	if (open->op_odstate)
		kmem_cache_free(odstate_slab, open->op_odstate);
}
