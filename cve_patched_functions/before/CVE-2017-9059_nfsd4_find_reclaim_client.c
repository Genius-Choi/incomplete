nfsd4_find_reclaim_client(const char *recdir, struct nfsd_net *nn)
{
	unsigned int strhashval;
	struct nfs4_client_reclaim *crp = NULL;

	dprintk("NFSD: nfs4_find_reclaim_client for recdir %s\n", recdir);

	strhashval = clientstr_hashval(recdir);
	list_for_each_entry(crp, &nn->reclaim_str_hashtbl[strhashval], cr_strhash) {
		if (same_name(crp->cr_recdir, recdir)) {
			return crp;
		}
	}
	return NULL;
}
