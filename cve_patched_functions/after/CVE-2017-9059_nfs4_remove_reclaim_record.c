nfs4_remove_reclaim_record(struct nfs4_client_reclaim *crp, struct nfsd_net *nn)
{
	list_del(&crp->cr_strhash);
	kfree(crp);
	nn->reclaim_str_hashtbl_size--;
}
