find_unconfirmed_client_by_name(struct xdr_netobj *name, struct nfsd_net *nn)
{
	lockdep_assert_held(&nn->client_lock);
	return find_clp_in_name_tree(name, &nn->unconf_name_tree);
}
