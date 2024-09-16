nfs4_release_reclaim(struct nfsd_net *nn)
{
	struct nfs4_client_reclaim *crp = NULL;
	int i;

	for (i = 0; i < CLIENT_HASH_SIZE; i++) {
		while (!list_empty(&nn->reclaim_str_hashtbl[i])) {
			crp = list_entry(nn->reclaim_str_hashtbl[i].next,
			                struct nfs4_client_reclaim, cr_strhash);
			nfs4_remove_reclaim_record(crp, nn);
		}
	}
	WARN_ON_ONCE(nn->reclaim_str_hashtbl_size);
}
