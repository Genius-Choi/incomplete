static void release_last_closed_stateid(struct nfs4_openowner *oo)
{
	struct nfsd_net *nn = net_generic(oo->oo_owner.so_client->net,
					  nfsd_net_id);
	struct nfs4_ol_stateid *s;

	spin_lock(&nn->client_lock);
	s = oo->oo_last_closed_stid;
	if (s) {
		list_del_init(&oo->oo_close_lru);
		oo->oo_last_closed_stid = NULL;
	}
	spin_unlock(&nn->client_lock);
	if (s)
		nfs4_put_stid(&s->st_stid);
}
