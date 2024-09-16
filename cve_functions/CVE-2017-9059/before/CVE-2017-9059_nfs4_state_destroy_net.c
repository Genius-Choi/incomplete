nfs4_state_destroy_net(struct net *net)
{
	int i;
	struct nfs4_client *clp = NULL;
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	for (i = 0; i < CLIENT_HASH_SIZE; i++) {
		while (!list_empty(&nn->conf_id_hashtbl[i])) {
			clp = list_entry(nn->conf_id_hashtbl[i].next, struct nfs4_client, cl_idhash);
			destroy_client(clp);
		}
	}

	for (i = 0; i < CLIENT_HASH_SIZE; i++) {
		while (!list_empty(&nn->unconf_id_hashtbl[i])) {
			clp = list_entry(nn->unconf_id_hashtbl[i].next, struct nfs4_client, cl_idhash);
			destroy_client(clp);
		}
	}

	kfree(nn->sessionid_hashtbl);
	kfree(nn->unconf_id_hashtbl);
	kfree(nn->conf_id_hashtbl);
	put_net(net);
}
